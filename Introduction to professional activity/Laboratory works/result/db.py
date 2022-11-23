import sqlite3 
import PyQt5 



conn = sqlite3.connect('Db.db')
cur = conn.cursor()




def add_data(id,type_of_cover,edition, payment_details, num_contract,price):
   cur.execute("""INSERT INTO printing_houses(id_print, date, cover, edition, payments, contract, price)
      VALUES (?, ?, ?, ?, ?, ?, ?);""",(id, 7, type_of_cover, edition, payment_details,num_contract,price))
   conn.commit()

add_data(id=int(input()),type_of_cover=int(input()),edition=int(input()),payment_details=int(input()),num_contract=int(input()),price=int(input()))