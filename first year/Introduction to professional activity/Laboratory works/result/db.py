import sqlite3 as sq
import time

conn = sq.connect('Db.db')
cur = conn.cursor()
id_orders: int = 0
while True:
    print("""Введите требуемую команду:Добавить типографию, Получить информацию о типографии, Добавить заказ, Найти исполненный заказ по названию книги, Удалить заказ, Вывести все книги автора""")
    command: str = input()
    match command:
        case "Добавить заказ":
            print("Введите: ФИО автора, название книги, тип переплета, тираж, реквезиты, номер контракта, общая цена контракта")

            def add_order() -> None:
                """Добавляет новый заказ в базу"""
                try:
                    query = """INSERT INTO orders(name, title, date, cover, edition, payments, contract, price)
                    VALUES (?, ?, ?, ?, ?, ?, ?,?);"""
                    cur.execute(query, (input(), input(), time.time(), input(),
                                        int(input()), int(input()), int(input()), int(input())))
                    conn.commit()

                except ValueError:
                    print("Все данные должны быть числом")
                    add_order()

                except sq.Error as error:
                    print("Ошибка", error)
            add_order()
        case "Найти исполненный заказ по названию книги":
            print("Введите название книги")

            def find_order() -> None:
                """Ищет заказ по id"""
                try:
                    query = """SELECT FROM orders WHERE title =? """
                    cur.execute(query, (input(),))
                    row = cur.fetchone()
                    print("ID заказа:", row[0])
                    print("ФИО:", row[1])
                    print("Тип переплета:", row[3])
                    print("Тираж:", row[4])
                    print("Количество страниц:", row[5])
                    print("№ контракта:", row[6])
                    print("Общая цена контракта:", row[7], end="\n\n")

                except sq.Error as error:
                    print("Ошибка", error)

            find_order()
        case "Удалить заказ":
            print("Введите название книги")

            def delete_order() -> None:
                """Удаляет заказ по названию книги"""
                try:
                    query = """DELETE FROM orders WHERE title =? """
                    cur.execute(query, (input(),))
                    conn.commit()

                except sq.Error as error:
                    print("Ошибка", error)

            delete_order()
        case "Вывести все книги автора":
            print('Введите ФИО автора')

            def find_company_orders(name=input()) -> None:
                """Ищет все книги автора"""
                try:
                    query = """SELECT * FROM orders"""
                    cur.execute(query)
                    for row in cur.fetchall():
                        if row[1] == name:
                            print("ID заказа:", row[0])
                            print("ФИО:", row[1])
                            print("Тип переплета:", row[3])
                            print("Тираж:", row[4])
                            print("Количество страниц:", row[5])
                            print("№ контракта:", row[6])
                            print("Общая цена контракта:", row[7], end="\n\n")

                except sq.Error as error:
                    print("Ошибка", error)

            find_company_orders()
        case "Добавить типографию":
            print('Введите название, номер контракта, реквезиты')

            def add_printing() -> None:
                """Добавляет типографию"""
                try:
                    query = """INSERT INTO printing_houses(name, contract, payments)
                    VALUES (?, ?, ?);"""
                    cur.execute(query, (input(), int(input()), int(input())))
                    conn.commit()
                except sq.Error as error:
                    print("Ошибка", error)
            add_printing()
        case "Получить информацию о типографии":
            print('Введите название типографии')

            def find_printing(name=input()) -> None:
                """Ищет все данные о типографии"""
                try:
                    query = """SELECT * FROM printing_houses"""
                    cur.execute(query)
                    for row in cur.fetchall():
                        if row[1] == name:
                            print("Название:", row[1])
                            print("№ Контракта:", row[2])
                            print("Реквезиты:", row[3])
                  
                except sq.Error as error:
                    print("Ошибка", error)
            find_printing()
        case _:
            print('Вы ввели команду неверно\n')
