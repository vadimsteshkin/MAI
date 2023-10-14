#include <iostream>

using namespace std;

struct Node{
        char data;
        Node * p;
};

int add_elem(Node * head, char ch)	// adding element to list
{
        cout << "adding element \"" << ch << "\" in " << head->data << " set." << endl;
        Node * p_ins = head; 		// pointer to move through list
        while ((p_ins->p != NULL) && (ch > p_ins -> p -> data))
					// while good: not end of list and next element fewer than insert symbol
                p_ins = p_ins ->p; 	// go to next element
        Node * new_node = new Node; 	// memory allocation for insert node
        new_node -> data = ch;		// copy symbol
        new_node -> p = p_ins -> p;	// copy pointer from current node to insert node
//        cout << "data: " << new_node -> data <<" adress: "<< new_node -> p << endl;
        p_ins -> p = new_node;		// copy address of new node to current node pointer
        return 0;			// here can be code of error
};

int delete_list(Node * head)		// delete all elements in list
{
	cout << "Delete all elements." << endl;
	Node * tmp;			// temporary ponter
	do{
		tmp = head->p;		// copy address next element after head in temporary pointer
					// because I don't allocate memory for head, I don't touch head
		head->p = tmp->p;	// I don't need first element and change poiter to address of next element in list
		delete tmp;		// delete old first element
	}while(head->p);		// while our set is not empty
	return 0;
}

int print_list(Node * head)		// printing set in standart form
{
        cout << head -> data << ": { ";
        Node * p_print = head;		// pointer to going throught list
        while (p_print->p)
        {
                p_print = p_print->p;	// getting address next element
                cout << p_print->data << ", ";
					// and printing it
        }
        cout << "}" << endl;
        return 0;
}

int main()
{
        Node head[5];			// this sets amount is enough
        head[0].data = 'A';		// adding first set
        head[0].p = nullptr;		// just in case
  //      cout << head.data << " " << head.p << endl;
        print_list(&head[0]);		// printing A
        add_elem(&head[0], 'b');	// adding element b in A
        print_list(&head[0]);
        add_elem(&head[0], 'e');	// adding element e in A
        print_list(&head[0]);
        add_elem(&head[0], 'a');	// ...
        print_list(&head[0]);
        add_elem(&head[0], 'c');	// ...
        print_list(&head[0]);		// printing A // it's sorted
	delete_list(&head[0]);		// delete all elements from A
	print_list(&head[0]);		// Yes, set in empty now
        return 0;
}