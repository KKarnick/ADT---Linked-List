
#include "ListLinked.h"

// ListNode member functions

template <typename DataType>
List<DataType>::ListNode::ListNode(const DataType& nodeData, ListNode* nextPtr){
	this->dataItem = nodeData;
	this->next = nextPtr;
}

// List member functions

template <typename DataType>
List<DataType>::List(int ignored = 0){
	head = 0;
	cursor = 0;
}

template <typename DataType>
List<DataType>::List(const List& other){
	    //head & cursor init at nullptr
	head = other.head;  //set value of head to same as other's head node
	ListNode* otherCurr = other.head;
	        //copy all nodes that exist in other
	while (otherCurr != 0) {      //set data and next ptr to same values as other's
		this->dataItem = otherCurr->dataItem;
		this->next = otherCurr->next;
		gotoNext();    //increment to next node in current (init. nullptr)
		otherCurr = otherCurr->next;   //increment other list to next node
	}
	cursor = other.cursor;
}

template <typename DataType>
List<DataType>& List<DataType>::operator=(const List& other){
	if(this ! = &other){   //check if referencing same List
		clear();  //first clear current List
		ListNode* otherCurr = other.head;   //declare ptr to other list's items, starting at head
		while (otherCurr != 0) {
			insert(otherCurr->dataItem);
		}

	}
}

template <typename DataType>
List<DataType>::~List(){
	clear();
}

template <typename DataType>
void List<DataType>::insert(const DataType& newDataItem) throw (logic_error){
	if (isEmpty()) {
		head = new ListNode(newDataItem, 0);
		cursor = head;
	}
	else {                     //can insert anywhere in middle of list w/this code
		cursor->next = new ListNode(newDataItem, cursor->next); //create new node w/param & make its next ptr the current cursor next
		cursor = cursor->next;
	}
}

template <typename DataType>
void List<DataType>::remove() throw (logic_error){
	if (isEmpty())
		throw logic_error("Empty list.");
	else {
		ListNode* nodeToRemove = cursor;
		gotoPrior();
		ListNode* prior = cursor;   //need to set next here
		prior->next = nodeToRemove->next;  //reset next to "go around" nodeToRemove
		delete nodeToRemove;		 //deallocate space from deleted node
		if(gotoNext() == false)
			gotoBeginning();  //set cursor to node after deleted node

	}
}

template <typename DataType>
void List<DataType>::replace(const DataType& newDataItem) throw (logic_error){
	if (isEmpty())
		throw logic_error("List is empty.");
	else 
		cursor->dataItem = newDataItem;  //replace current node's data with newDataItem
}

template <typename DataType>
void List<DataType>::clear(){
	if (head == 0)     //empty list, do nothing
		return;
	while (head->next != 0) {
		cursor = head->next;  //cycle through list, moving head to next location then deleting head
		delete head;
		head = cursor;  //update head to next location after deletion and continue loop
	}
	delete head;  //when only one node left, delete final node & update head and cursor
	head = 0;
	cursor = 0;
}

template <typename DataType>
bool List<DataType>::isEmpty() const{
	if (head == 0)
		return true;
	else
		return false;
}

template <typename DataType>
bool List<DataType>::isFull() const{
	return false;
}

template <typename DataType>
void List<DataType>::gotoBeginning() throw (logic_error){
	if (isEmpty())
		throw logic_error("List is empty.");
	else
		cursor = head;    //head is always beginning of list
}

template <typename DataType>
void List<DataType>::gotoEnd() throw (logic_error){
	if (isEmpty())
		throw logic_error("List is empty.");
	else {
		while (cursor->next != 0)
			cursor = cursor->next;    //iterates throgh list until tail (end) is found (tail->next is nullptr)
	}
}

template <typename DataType>
bool List<DataType>::gotoNext() throw (logic_error){
	if(isEmpty() )
		throw logic_error("List is empty.");
	else {
		if (cursor->next != 0) {  //if there IS a next node in list, move cursor
			cursor = cursor->next;
			return true;
		}
		else   //cursor's next is nullptr (no next node in list)
			return false;
	}
}

template <typename DataType>
bool List<DataType>::gotoPrior() throw (logic_error){
	if (isEmpty())
		throw logic_error("List is empty.");
	else {
		if (cursor == head)  //beginning of list, cannot move to prior
			return false;
		else {
			ListNode* curr = head;
			while(curr != 0){
				if (curr->next == cursor){ //found node before cursor
					cursor = curr;   //set cursor to node before
					return true;
				}
				else 
					curr = curr->next;
			}
			return false;
		}
	}
}

template <typename DataType>
DataType List<DataType>::getCursor() const throw (logic_error){
	if (isEmpty())
		throw logic_error("List is empty.");
	else {
		return cursor->dataItem;
	}
}

template <typename DataType>
void List<DataType>::moveToBeginning () throw (logic_error){
	if (isEmpty())
		throw logic_error("List is empty.");
	else {
		ListNode* curr = cursor;  //node to be moved to beginning of list
		gotoPrior();   //move cursor
		cursor->next = curr->next;  //cursor now points to node after curr
		curr->next = head;
		head = curr;
		cursor = head;
	}
}

template <typename DataType>
void List<DataType>::insertBefore(const DataType& newDataItem) throw (logic_error){  //inserts item before cursor location
	if (isEmpty()) {
		head->dataItem = newDataItem;
		head->next = 0;
		cursor = head;
	}
	else {
		ListNode* currLocation = cursor;  //holds cursor's current location
		gotoPrior();
		cursor->next = new ListNode(newDataItem, currLocation);  //create new node whose next is the insert location (moves that one down one spot) 
		gotoNext();   //move cursor to new item's location
	}
}

#include "show5.cpp"

