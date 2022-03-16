/*
 * List.h
 *
 *  Created on: Jun 1, 2021
 *      Author: OS1
 */

#ifndef LIST_H_
#define LIST_H_

//class PCB;

template<class T>
class LList{
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

	void add(T * t){
		if(!head) head = tail = new Node(t);
		else {
			tail->next = new Node(t);
			tail = tail->next;
		}
	}

	T* remove(T* t){ //brisemo element - TESTIRAJ
		T * removedT = 0;
		if(head){
			if(this->count() == 1){
				Node * deleted = head;            //TESTIRAJ
				head = tail = 0;
				removedT = deleted->tt;
				deleted->tt = 0;
				delete deleted;
				return removedT;
			}

			Node * curr = head;                  //TESTIRAJ
			Node * prev = 0;
			Node * next = head->next;

			while(curr != 0 && curr->tt != t){
				prev = curr;
				curr = next;
				next = curr->next;
			}

			if(!curr) return 0; //ako nema

			Node * deleted = curr;               //TESTIRAJ

			if(deleted == head) head = next;
			if(deleted == tail) tail = prev;
			if(prev) prev->next = next;

			removedT = deleted->tt;
			deleted->tt = 0;
			delete deleted;
		}
		return removedT; //ako treba obrisani pcb odkomentarisati
	}

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

	T * getCurr() {
		return curr->tt;
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


	T * getPointer(){
		if(!curr) return 0;

		return curr->tt;
	}

	LList(){
		head = tail = curr = 0;
	}

	virtual ~LList(){
		/*while(head != 0){
					Node * old = head;
					head = head->next;
					delete old;
		}

		tail = 0;*/
	}
};



#endif /* LIST_H_ */
