#define QUEUE_SIZE   50
enum errorType {DOWNFLOW,OVER_FLOW,SUCCESS,ERROR_INDEX};

template<class T>
class queue
{
public:
	queue();
	int isEmpty()const;
	void Clean();
	int isFull()const;
	errorType enQueue(const T );
	void enQueueEx(const T );
	errorType delQueue();
	int size()const;
	errorType getFront(T &)const;
	errorType getLast(T &)const;
        errorType getAny(T &,int i)const;
private:
	int count,rear,front;
	 T data[QUEUE_SIZE];
};


template<class T>
queue<T>::queue()
{
	count=0;
	rear=front=0;
}


template<class T>
int queue<T>::isEmpty()const
{
	 if(rear==front)return 1;
	 else return 0;
}


template<class T>
int queue<T>::isFull()const
{
	 if((rear+1)%QUEUE_SIZE==front)return 1;
	 else return 0;
}


template<class T>
void queue<T>::Clean()
{
	 count=0;
	rear=front=0;
}


template<class T>
errorType queue<T>::delQueue()
{
	if(isEmpty())return DOWNFLOW;
	else
	{
		front=(front+1)%QUEUE_SIZE;
		count--;
		return SUCCESS;
	}
}


template<class T>
errorType queue<T>::enQueue(const T x)
{
	if(isFull())delQueue();
	rear=(rear+1)%QUEUE_SIZE;
	data[rear]=x;
	count++;
	return SUCCESS;
}


template<class T>
void queue<T>::enQueueEx(const T x)
{
	if (isFull()) delQueue();
	enQueue(x);
}


template<class T>
errorType queue<T>::getFront(T &x)const
{
	if(isEmpty())return DOWNFLOW;
	else
	{
		x=data[(front+1)%QUEUE_SIZE];
		return SUCCESS;
	}
}


template<class T>
errorType queue<T>:: getAny(T &x,int i)const
{
   if(i>count||i<1)return ERROR_INDEX;
   else 
   {
      x=data[(front+i)%QUEUE_SIZE];
      return SUCCESS;
   }
}

template<class T>
errorType queue<T>::getLast(T &x)const
{
	return getAny(x, count);
}


template<class T>
int queue<T>::size()const
{
	return count;
}

