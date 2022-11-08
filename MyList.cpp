#include <iostream>
#include <string>

using namespace std;

class Node{
    private:
        int content;
        Node *NextNode;
        Node *PriorNode;
    public:
        int getContent(){
            return content;
        }
        void setContent(int value){
            this->content = value;
        }
        Node *getNextNode(){
            return NextNode;
        }
        void setNextNode(Node *nextNode){
            this->NextNode = nextNode;
        }
        Node *getPriorNode(){
            return PriorNode;
        }
        void setPriorNode(Node *priorNode){
            this->PriorNode = priorNode;
        }
};

class MyList{
    private:
        Node *head;
        Node *tail;
        int nElements;
    public:
        MyList(){
            this->head = NULL;
            this->tail = NULL;
            this->nElements = 0;
        }

        bool IsEmpty(){
            if(nElements == 0){
                return true;
            }else{
                return false;
            }
        }

        int Length(){
            return nElements;
        }

        int GetIndexOf(int value){
            Node *aux = head;
            int cont = 1;
            if (IsEmpty()){
                return -1;
            }

            while (aux->getNextNode() != NULL){
                if (aux->getContent() == value){
                    return cont;
                }
                aux = aux->getNextNode();
                cont++;
            }
            return -1;
        }

        bool Contains(int value){
            Node *aux = head;
            if (IsEmpty()){
                return false;
            }

            while (aux->getNextNode() != NULL){
                if (aux->getContent() == value){
                    return true;
                }
                aux = aux->getNextNode();
            }
            return false;
        }

        bool AddFirst(int value){
            Node *newNode = new Node();

            newNode->setContent(value);
            newNode->setNextNode(head);
            newNode->setPriorNode(NULL);

            if(IsEmpty()){
                tail = newNode;
            }else{
                head->setPriorNode(newNode);
            }
            head = newNode;
            nElements++;
            return true;
        }


        bool AddLast(int value){
            Node *newNode = new Node();
            newNode->setContent(value);
            newNode->setNextNode(NULL);

            tail->setNextNode(newNode);

            newNode->setPriorNode(tail);
            tail->setNextNode(newNode);
            tail = newNode;

            nElements++;
            return true;
        }

        bool Add(int pos, int value){
            if((IsEmpty()) && pos != 1){
                return false;
            }
            if (pos == 1){
                return AddFirst(value);
            }else if(pos == nElements +1){
                return AddLast(value);
            }
        }

        int RemoveFirst(){
            Node *aux = head;
            int value_removido = aux->getContent();
            if (nElements == 1){
                head = NULL;
                tail = NULL;
            }else{
                head = aux->getNextNode();
                aux->getNextNode()->setPriorNode(NULL);
            }
            nElements--;
            delete aux;
            return value_removido;
        }


        int RemoveLast(){
            Node *aux = tail;
            int value_removido = aux->getContent();

            aux->getPriorNode()->setNextNode(NULL);
            tail = aux->getPriorNode();

            nElements--;
            delete aux;

            return value_removido;
        }

        int RemoveAt(int pos){
            if (IsEmpty()){
                return false;
            }
            if (pos==1){
                return RemoveFirst();
            }else if (pos == Length()){
                return RemoveLast();
            }
        }
        
};

