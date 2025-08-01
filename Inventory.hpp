#ifndef INVENTORY_HPP
#define INVENTORY_HPP

template<typename T>
class Inventory
{
    private:
    T* items;
    int size;
    int capacity;
    void resize();

    public:
    Inventory();
    int getSize() const;
    T* getArray() const;
    void addItem(const T& item);
    void removeItem(int index);
    T getItem(int index) const;
    ~Inventory();
};

template<typename T>
void Inventory<T>::resize()
{
    int newCapacity=capacity*2;
    T* newItems=new T[newCapacity];
    for(int i=0;i<=size;i++)
    {
        newItems[i]=items[i];
    }
    delete[] items;
    items=newItems;
    capacity=newCapacity;
}

template<typename T>
Inventory<T>::Inventory()
{
    size=-1;
    capacity=15;
    items=new T[capacity];
}

template<typename T>
int Inventory<T>::getSize() const {return size;}

template<typename T>
T* Inventory<T>::getArray() const {return items;}

template<typename T>
void Inventory<T>::addItem(const T& item)
{
    if(capacity==size)
        resize();
    items[++size]=item;
}

template<typename T>
void Inventory<T>::removeItem(int index)
{
    if(index<0||index>size)
        return;
    for(int i=index;i<size;i++)
    {
        items[i]=items[i+1];
    }
    size--;
}

template<typename T>
T Inventory<T>::getItem(int index) const
{
    return items[index];
}

template<typename T>
Inventory<T>::~Inventory()
{
    delete[] items;
}

#endif