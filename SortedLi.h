/*
 * SortedList.h
 *
 *  Created on: Jun 20, 2021
 *      Author: OS1
 */

#ifndef SORTEDLI_H_
#define SORTEDLI_H_


template<class T>
class SortedList{
public:
	struct Node{
	public:
		T * tt;
		Node * next;

		Node(T * t, Node * n = 0){
					tt = t;
					next = n;
		}
	};

	Node * head;
	Node * tail;
	Node * curr;

	void add(T * t){ //add + sort
		Node * newNode = new Node(t);

		if(!head) head = tail = newNode;
		else if(*t <= *head->tt){
			newNode->next = head;
			head = newNode;
		}
		else {
			for(toHead(); hasCurr() && hasCurrNext() && *t >= *(curr->next->tt); toNext()){
					//
			}

			if(curr == tail){
				tail->next = newNode;
				tail = newNode;
			}
			else {
				newNode->next = curr->next;
				curr->next = newNode;
			}

		}
	}

	/*void remove(T* t){ //brisemo element - TESTIRAJ

		if(head){
			if(this->count() == 1){
				Node * deleted = head;            //TESTIRAJ
				head = tail = 0;
				deleted->tt = 0;
				delete deleted;
				return;
			}

			Node * curr = head;                  //TESTIRAJ
			Node * prev = 0;
			Node * next = head->next;

			while(curr != 0 && curr->tt != t){
				prev = curr;
				curr = next;
				next = curr->next;
			}

			if(!curr) return; //ako nema

			Node * deleted = curr;               //TESTIRAJ

			if(deleted == head) head = next;
			if(deleted == tail) tail = prev;
			if(prev) prev->next = next;

			deleted->tt = 0;
			delete deleted;
		}
		//return removedT; ako treba obrisani pcb odkomentarisati
	}*/

	void remove(){ //s pocetka brisemo
		//T * removedT = 0; //ako nista ne brisemo, nemamo ni pcb koji brisemo
		if(head){
			Node * deleted = head;
			//removedT = deleted->tt;
			head = head->next;
			if(!head) head = tail = 0;
			deleted->tt = 0; //ne zelimo da obrisemo pcb !!!
			delete deleted;
		}
		//return removedT; ako treba obrisani pcb odkomentarisati
	}

	void removeFromEnd(){ //s kraja brisemo
			if(!head) return;

			Node * temp = head;
			Node * prev = 0;
			while(temp->next){
				prev = temp;
				temp = temp->next;
			}

			Node * deleted = tail;
			//removedT = deleted->tt;
			tail = prev;
			if(!tail) head = tail = 0;

			deleted->tt = 0;
			delete deleted;
			tail->next = 0;
		}

	int count(){
		Node * temp = head;
		int counter = 0;
		while(temp){
			counter++;
			temp = temp->next;
		}

		return counter;
	}

	T * getHead() {
		return head->tt;
	}

	T * getTail() {
			return head->tt;
	}

	void toHead() {
		curr = head;
	}

	void toNext(){
		if(curr) curr=curr->next;
	}

	int hasCurr(){
		return curr != 0;
	}

	int hasCurrNext(){
			return curr->next != 0;
	}


	T * getPointer(){
		if(!curr) return 0;

		return curr->tt;
	}

	SortedList(){
		head = tail = curr = 0;
	}

	virtual ~SortedList(){
		/*while(head != 0){
					Node * old = head;
					head = head->next;
					delete old;
		}

		tail = 0;*/
	}
};

#endif /* SORTEDLI_H_ */
