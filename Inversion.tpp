#include "Inversions.h"

template<class T>
int CountInversions(
    const ICollection<T>& collection,
    bool (*compare)(T,T)
){
    if (compare == nullptr) throw InvalidArgument("CountInversions(): compare function is null");
    if (collection.GetCount() == 0) return 0;

    int result = 0;
    MutableArraySequence<T>* helper = new MutableArraySequence<T>();
    helper->Append(collection.Get(0));
    for (int i=1; i<collection.GetCount(); i++){
        int helperLenght = helper->GetLength();
        T item = collection.Get(i);
        int index = helperLenght;
        for(int j=helperLenght-1; j>=0; j--){
            if(compare(item,helper->Get(j))){
                result++;
                index=j;
            }
            else
            {
            break;
            }
        }
        helper->InsertAt(item, index);
    }
    delete helper;
    return result;
}
