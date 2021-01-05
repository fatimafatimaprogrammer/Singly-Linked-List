/************************************************************************8
Name: Urooj Fatima Raza
cms:289365
DSA ASSIGNMENT #1
"implementation of different methods for singly linked list"
****************************************************************************/

#include<iostream>
using namespace std;

/*
DEFINING THE STRUCTURE FOR SINGLY LINKED LIST
*/
class Node {
public:
	int data;
	Node* next;
};

//now implementing the main class
class LinkedList {
public:
	Node* startNode;//it stores the address of starting node in list
	Node* lastNode;//it stores the address of last node of list
	Node* ploc;//a special variable we use in search function to store address of logical pre-decessor of value in list 
	Node* loc;//to be used by Search(value) method to store address of the node containing the searched value in a list.If it is not found it contains NULL.
	
	/*
	Constructor for creating the empty linked list by assigning start, loc, ploc pointer variables to null
	*/
	LinkedList() {
		startNode = NULL;
		loc = NULL;
		ploc = NULL;
	}

	//implementation of isEmpty() method
	bool isEmpty() {
		return startNode == NULL;
	}

	//implementationof printList() method
	void printlist() {
		Node* temp = startNode;
		while (temp != NULL) {
			cout << temp->data << "  ";
			// advance temp to successor node.
			temp = temp->next;
		}
		cout << "\n";
		return;

	}
	//implementation of function for printing reverse order of list by using arrays
	void printReverse(){
		Node* temp = startNode;
		int i = 0;
		int arr[15] ;
		for (int i = 0; i < 15; i++) {
			arr[i] = 0;
		}
		while (temp != NULL) {
			//adding elements of list to array 
			arr[i] = temp->data;
			temp = temp->next;
			i++;
		}
		
	//printing the array in reverse order
		for (int j = 14; j >= 0; j--) {
			if(arr[j]!=0)
			cout <<  arr[j] << " ";
		}	
		cout << "\n";
	}

	//implementation of method for printing reverse linked list  using "RECURSIVE APPROACH"
	void printReverse(Node* startNode) {
		if (startNode == NULL)
			return;
		printReverse(startNode->next);
		cout << startNode->data << " ";
		cout << "\n";
	}

	//implementationof InsertAtFront() method
	void InsertAtFront(int value) {
		//first we have to allocate memory by making object of linkedlist structure
		Node* newnode = new Node();
		newnode->data = value;

		//one case is when list is empty so start and last both should be updated
		if (isEmpty()) {
			startNode = newnode;
			lastNode = newnode;
		}
		else
		{
			newnode->next = startNode;
			startNode = newnode;
		}
		//print the inserted elements
		printlist();

	}

	//implementationof InsertAtEnd() method
	void InsertAtEnd(int value) {
		//first we have to allocate memory by making object of linkedlist structure
		Node* newnode = new Node();
		newnode->data = value;

		if (isEmpty()) {
			startNode = newnode;
			lastNode = newnode;
		}
		else {
			lastNode->next = newnode;
			lastNode = newnode;
		}
		//printing the list after insertion
		printlist();
	}

	//implementationof InsertSorted() method
	//if we want to maintain a sorted list we call this function
	void InsertSorted(int value) {
		Search(value);
		if (loc != NULL) {
			cout << "VALUE IS ALREADY IN THE LIST AND DUPLICATION IS NOT ALLOWED" << endl;
		}
		else   //if vaalue is not found then insert in its logicall position
		{
			if (ploc == NULL) {
				InsertAtFront(value);
			}
			else
			{
				Node* newnode = new Node();
				newnode->data = value;
				newnode->next = ploc->next;
				ploc->next = newnode;

				//one special case if ploc is the last 
				if (ploc == lastNode) {
					lastNode = newnode;
				}
			}

		}

	}

	//implementationof Search() method
	void Search(int value) {
		loc = startNode;
		ploc = NULL;

		//IF LIST IS EMPTY THEN CONTROL EXITS FROM THE FUNCTION
		if (isEmpty())
			return;

		while (loc != NULL && loc->data < value)
		{
			ploc = loc;
			loc = loc->next;
		}

		//THIS LOOP EXECUTES WHEN THE VALUE DOES NOT FOUND IN THE LIST
		if (loc != NULL && loc->data != value)
		{
			loc = NULL;
		}
	}

	//implementationof DeleteValue() method
	void DeleteValue(int value) {
		Search(value);
		if (loc != NULL)//if value is found in list
		{
			if (ploc==NULL)//if value is first node
			{
				//if list contains only one element 
				if (loc == lastNode)
				{
					startNode = NULL;
					lastNode = NULL;
					delete loc;
				}
				else {
					startNode = startNode->next;
					delete loc;
				}
			}
			else
			{
				if (loc==lastNode) {
					lastNode = ploc;
					ploc->next = loc->next;
					delete loc;
				}
				else
				{
					lastNode = ploc;
					ploc->next = loc->next;
					delete loc;
				}
			}
		}
		else
		{
			cout << "^^^^^^^^^^^^^^^^^^^^^^^^^^\nVALUE NOT FOUND!!!!!!!! SO DELETION NOT POSSIBLE\n^^^^^^^^^^^^^^^^^^^^^^^\n" << endl;
		}

	}

	//implementation of method that deletes odd data values of list
	void deleteODDvalues() {
		Node* current = startNode;
	    Node* even;

		// iterate until the first even element, or the end
		while (current != NULL && current->data % 2 != 0)
		{
			current = current->next;
		}

		// the new start is the first even element, or the end
		startNode = current;

		// if there is no other element then return
		if (current == NULL) {
			return;
		}

		// the  even element is the current element
		even = current;

		// we know the current element is even, and not null, so moving on
		current = current->next;

		// iterate until the end
		while (current != NULL)
		{
			// is the current element even?
			if (current->data % 2 == 0) {
				even->next = current;
				even = current;
			}
			current = current->next;
		}

		// last even might still point to an odd valued element, so NULL it out
		even->next = NULL;
		printlist();
	}

	/*implementation of function that reverse the order of sll recusively*/
	Node * recursivelyReverseOrder(Node *start) {
		/* base case :if list is empty simply returns  */
		if (start == NULL)
			return NULL;
		/*other base case : if list has only one node order cannot be reversed */
		if (start->next == NULL) {
			startNode=start;
			return start;
		}

		/*now recursive case: if their are more than one node*/
		Node* newnode = recursivelyReverseOrder(start->next);
		newnode->next = start;
		start->next = NULL;
		return start;
	}

	//implementation of method that reverse the order of linked list
	void reverseOrder() {
		//Initialize three pointers prev as NULL, curr as head and next as NULL.
		Node* previous = NULL;
		Node* current = startNode;
		Node* next = NULL;
			
		while (current != NULL)
		{
			/*updating next previous and current */
			next = current->next;
			current->next = previous;
			previous = current;
			current = next;
		}

		startNode=previous;
		printlist();
	}

	/*Implement a function that rearranges a singly linked list by separately connecting the odd positioned nodes in the same order, 
	and the even positioned nodes in the reverse order.Finally, connect the reversed sub-list of
	the even positioned nodes before the odd positioned nodes. Finally, update the start and last pointer variables.*/

	void evenoddRecursively(Node* node,LinkedList *evenlist,int listelement,Node *evennode) {
		/* base case :if list is empty simply returns  */
		if (node == NULL) {
			//cout << "base case: null node \n";
			return;
		}
		/*recursive case : traverse list and print only even nodes in reverse order */
		if (node->next != NULL) {
			listelement++;
			//cout << "calling for list element #  " << listelement << endl;
			//inserting only even values in evenlist
			if (node->data % 2 == 0)
			{
				evennode = node;
				//cout << "\n evennode->data " << evennode->data << endl<<endl;
			}
			evenoddRecursively(node->next, evenlist, listelement, evennode);
			listelement--;
			//cout << "End of listelement # " << listelement << endl;
		}
		/*deleting even element from original list and inserting it at last of even list*/
		int current = node->data;
		if (current % 2 == 0) {
			DeleteValue(current);
			evenlist->InsertAtEnd(current);
		}
		/*at last after connecting even list delete that temporaray list*/
		if (listelement == 0 && !(evenlist->isEmpty())) {
			evenlist->lastNode->next = this->startNode;
			this->startNode = evenlist->startNode;
			delete evenlist;
		}
	}
	//implementation of method that rearranges the even and odd numbered values in their datafield
	void EvenOdd() {
		Node* last = startNode;
		Node* previous = NULL;
		Node* current= startNode;

		/*pointing to the last node */
		while (last->next != NULL)
			last = last->next;

		Node* new_last = last;

		/* moving all odd nodes at last */
		while (current->data % 2 != 0 && current != last)
		{
			new_last->next = current;
			current = current->next;
			new_last->next->next = NULL;
			new_last = new_last->next;
		}

	
		/*case: if
		there is any even node */
		if (current->data % 2 == 0)
		{
			/* making the current to be starting node */
			startNode = current;

			/* current pointer pointing to the first even node */
			while (current != last)
			{
				//checking if its even
				if ((current->data) % 2 == 0)
				{
					previous = current;
					current = current->next;
				}
				else
				{
					previous->next = current->next;

					/*  next of current as NULL */
					current->next = NULL;

					new_last->next = current;
					new_last = current;
					current = previous->next;
				}
			}
		}
		else {
			previous = current;
		}
			

		/* CASE: If there are more than 1 odd nodes
		and end of original list is odd */
		if (new_last!= last && (last->data) % 2 != 0)
		{
			previous->next = last->next;
			last->next = NULL;
			new_last->next = last;
		}
		return;
	}

	/*
	5.	Write a function which takes two values as input from the user and searches them in the list.
	If both the values are found, your task is to swap both the nodes in which these values are found. 
	*/
	void specialFunction(int val1, int val2)
	{

		//case: if both values are same   
		if (val1 == val2)
		{
			cout << "both values entered by user are same so they cannot be swapped !!!!!!!!!!!" << endl;
			return;
		}

		/*
		case: for tracking the val1 and initilizing 
		pointers for previous and current of val1
		*/
		Node* prev_of_val1 = NULL, * current_val1 = startNode;
		while (current_val1->data != val1)
		{
			prev_of_val1 = current_val1;
			current_val1 = current_val1->next;
		}

		/*
		case: for tracking the val2 and initilizing
		pointers for previous and current of val2
		*/
		Node* prev_of_val2 = NULL, * current_val2 = startNode;
		while (current_val2->data != val2)
		{
			prev_of_val2 = current_val2;
			current_val2 = current_val2->next;
		}

		/*case: when any one of the value is not present
		* then we are done by only returning
		*/
		if (current_val1 == NULL || current_val2 == NULL)
		{
			cout << "it seems that one or both values user entered is not in the linked list so nothing happens " << endl;
			return;
		}
		

		/*case: if val1 is not the front node
		* means previous is not null
        */
		if (prev_of_val1 != NULL)
			prev_of_val1->next = current_val2;
		else // Else make val2 as new starting node
			startNode = current_val2;

		/*case: if val2 is not the front node
		* means previous is not null
		*/
		if (prev_of_val2 != NULL)
			prev_of_val2->next = current_val1;
		else // Else make val1 as new starting node
			startNode = current_val1;

		// Swap next pointers  
		Node* temp = current_val2->next;
		current_val2->next = current_val1->next;
		current_val1->next = temp;
		printlist();
	}
	

	//implementationof DestroyList() method
	void DestroyList() {
		while (startNode != NULL)
		{
			Node* temp = new Node();
			temp = startNode;
			startNode = startNode->next;
			delete temp;
		}
		lastNode = NULL;
		cout << "******************************\n yayyyyyy !! all elements of list are destroyed\n*********************************";
		printlist();
	}

	/*Implement a function takes a position number pos as input from the user, and returns the value stored at that position.*/
	template<class T>
	T get_pos(int pos) {
		if (pos == 1) {
			// Get the first element
			return this->startNode->data;
		}
		else {
			// Get the index'th element
			Node* temp = new Node();
			temp=this->startNode;
			for (int i = 2; i <=pos; ++i) {
				temp = temp->next;
			}
			cout << "the value at position : " << pos << " is : " << temp->data << endl;
			return  temp->data;
		}
	}



};

/*
HERE GOES OWR MAIN CODE FOR TESTING THE METHODS OF SINGLY LINKED LIST
*/
int main() {
	LinkedList* obj = new LinkedList();
	LinkedList* obj1 = new LinkedList();
	Node* node = new Node();

	int value1 = 0; int value2 = 0;
	cout << "------------------------------------------------------------\n\t\" SINGLY LINKED LIST\"\t\n------------------------------------------------------------\n";
	cout << endl << "INSERTING 1 AT FRONT using InsertAtFront(11)\n" << endl;
	obj->InsertAtFront(1);


	cout << endl << "INSERTING 13,15,14,16,12 USING  InsertSorted()\n" << endl;
	obj->InsertSorted(19);
	obj->InsertSorted(12);
	obj->InsertSorted(8);
	obj->InsertSorted(7);
	obj->InsertSorted(2);
	obj->printlist();

	cout << endl << "INSERTING 9 AT END using  InsertAtEnd(7)\n" << endl;
	obj->InsertAtEnd(9);
	
	//cout << "###############################################################\n";
		//"\nImplementing  a function that takes a position number pos as input from the user, and returns the value stored at that position.\n\n";
	//cout<< obj->get_pos<int>(2) <<
	//obj->recursivelyReverseOrder(obj->startNode);
	cout << "recursively rearranging even odd valued nodes\n first arranging even valued node\n";
	int listelement = 0;
	obj->evenoddRecursively(obj->startNode,obj1,listelement,obj1->startNode);
	cout << endl << "\n******************************************************************\n";
	obj->printlist();
	cout << endl << "\n******************************************************************\n";
	/*
	* TESTING OF ASSIGNMENT METHODS
	* 
	cout <<endl<< "******************************************************************\n";
	cout <<" (1) printing the reverse :" << endl;   
	obj->printReverse(obj->startNode);
    cout  << " (3) reversing the order of linked list.\n " << endl;
	obj->reverseOrder();
	cout << endl << "(4) rearranging the even and odd numbered values in the linked list" << endl;
	obj->EvenOdd();
	obj->printlist();
	cout  << " (5) swap both the nodes in which these values are found."
		"Note, that you are not supposed to swap values."
		"You are supposed to change next pointer fields in the concerned nodes." << endl;
	obj->specialFunction(4,6);
	cout << endl << " (2) deleting all odd values in the list " << endl;
	obj->deleteODDvalues();
	cout << "******************************************************************\n";
	*/

	/*cout <<endl<< "Deleting value 5 using DeleteValue(5) \n" << endl;
	obj->DeleteValue(5);
	obj->printlist();

	cout << endl << "Deleting value 1 using DeleteValue(5) \n" << endl;
	obj->DeleteValue(1);
	obj->printlist();

	cout << endl << "Deleting value 10 which is not in list so list remains the same\n" << endl;
	obj->DeleteValue(10);
	obj->printlist();

	cout << endl << "Destroying full linked list so that it contained no elements \n" << endl;
	obj->DestroyList();*/
}
