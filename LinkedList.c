#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "../inc/LinkedList.h"
#include "LinkedList.h"

static Node* getNode(LinkedList* this, int nodeIndex);
static int addNode(LinkedList* this, int nodeIndex,void* pElement);

/** \brief Crea un nuevo LinkedList en memoria de manera dinamica
 *
 *  \param void
 *  \return LinkedList* Retorna (NULL) en el caso de no conseguir espacio en memoria
 *                      o el puntero al espacio reservado
 */
LinkedList* ll_newLinkedList(void)
{
    LinkedList* this;

    this = (LinkedList*) malloc(sizeof(LinkedList));
    if(this!=NULL)
    {
        this->size = 0;
        this->pFirstNode = NULL;
    }

    return this;
}

/** \brief Retorna la cantidad de elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna (-1) si el puntero es NULL o la cantidad de elementos de la lista
 *
 */
int ll_len(LinkedList* this)
{
    int returnAux = -1;
    if(this!=NULL)
    {
        returnAux = this->size;
    }

    return returnAux;
}


/** \brief  Obtiene un nodo de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
static Node* getNode(LinkedList* this, int nodeIndex)
{
    Node* pNode = NULL;
    int cont = 0;

    if(this != NULL)
    {
        if(nodeIndex >= 0 &&  nodeIndex < ll_len(this))
        {

            pNode = this->pFirstNode;
            while(pNode->pNextNode != NULL && cont != nodeIndex)
            {
                pNode = pNode->pNextNode;
                cont++;
            }
        }
    }

    return pNode;
}

/** \brief  Permite realizar el test de la funcion getNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param index int Indice del nodo a obtener
 * \return Node* Retorna  (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        (pElement) Si funciono correctamente
 *
 */
Node* test_getNode(LinkedList* this, int nodeIndex)
{
    return getNode(this, nodeIndex);
}


/** \brief Agrega y enlaza un nuevo nodo a la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
static int addNode(LinkedList* this, int nodeIndex,void* pElement)
{

    int returnAux = -1;
    Node* prev;
    //Node* next;
    Node* nuevoNodo;


    if(this != NULL)
    {
        if(nodeIndex >= 0 && nodeIndex <= ll_len(this))
        {
            nuevoNodo = (Node*) malloc(sizeof(Node));
            if(nuevoNodo != NULL)
            {
                nuevoNodo->pElement = pElement;
                nuevoNodo->pNextNode = NULL;
                if(nodeIndex == 0)
                {
                    nuevoNodo->pNextNode = this->pFirstNode;
                    this->pFirstNode = nuevoNodo;
                    this->size++;
                    returnAux = 0;
                }
                else
                {
                    prev  =  getNode(this,nodeIndex-1);
                    if(prev != NULL)
                    {
                        nuevoNodo->pNextNode = prev->pNextNode;
                        prev->pNextNode = nuevoNodo;
                        this->size++;
                        returnAux = 0;
                    }
                }
            }
        }
    }

    return returnAux;
}


/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo nodo
 * \param pElement void* Puntero al elemento a ser contenido por el nuevo nodo
  * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int test_addNode(LinkedList* this, int nodeIndex,void* pElement)
{
    return addNode(this,nodeIndex,pElement);
}


/** \brief  Agrega un elemento a la lista
 * \param pList LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento a ser agregado
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_add(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    //int indice = 0;
    //Node* actual;

    if(this != NULL)
    {
        if(addNode(this,ll_len(this),pElement) == 0)
        {
            returnAux = 0;
        }
    }

    return returnAux;
}

/** \brief Permite realizar el test de la funcion addNode la cual es privada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a obtener
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_get(LinkedList* this, int index)
{
    void* returnAux = NULL;
    Node* aux = NULL;

    if(this != NULL)
    {
        if(index >= 0 && index < ll_len(this))
        {
            aux = getNode(this,index);
            if(aux != NULL)
            {
                returnAux = aux->pElement;
            }
        }
    }

    return returnAux;
}


/** \brief Modifica un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a modificar
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_set(LinkedList* this, int index,void* pElement)
{
    int returnAux = -1;
    Node* actual;
    //int cantidad;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {
        actual = getNode(this,index);
        if(actual != NULL)
        {
            actual->pElement = pElement;
            returnAux = 0;
        }
    }

    return returnAux;
}


/** \brief Elimina un elemento de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento a eliminar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_remove(LinkedList* this,int index)
{
    int returnAux = -1;
    Node* aux = NULL;
    Node* next = NULL;
    Node* before = NULL;
    //int indice = 0;

    if(this != NULL && index >= 0 && index < ll_len(this))
    {

        aux = getNode(this,index);
        next = aux->pNextNode;
        if(index == 0 && aux != NULL && next != NULL)
        {
            this->pFirstNode = next;
        }
        else
        {
            before = getNode(this,index-1);
            if(before != NULL)
            {
                //before->pNextNode = aux->pNextNode;
                before->pNextNode = next;
            }
        }
        free(aux);
        this->size--;
        returnAux = 0;
    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_clear(LinkedList* this)
{
    int returnAux = -1;
    //Node* nodo = NULL;
    //Node* aux = NULL;
    //int i;

    if(this != NULL)
    {

        while(ll_len(this) != 0)
        {
            ll_remove(this,ll_len(this));
            this->size--;
        }
        if(ll_len(this) == 0)
        {
            returnAux = 0;
        }

    }

    return returnAux;
}


/** \brief Elimina todos los elementos de la lista y la lista
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si funciono correctamente
 *
 */
int ll_deleteLinkedList(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        ll_clear(this);
        free(this);
        returnAux = 0;
    }

    return returnAux;
}

/** \brief Busca el indice de la primer ocurrencia del elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero al elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        (indice del elemento) Si funciono correctamente
 *
 */
int ll_indexOf(LinkedList* this, void* pElement)
{
    int returnAux = -1;
    Node* nodo = NULL;

    if(this != NULL)
    {
        nodo = this->pFirstNode;
        if(nodo != NULL)
        {
            for(int i = 0; i < ll_len(this); i++)
            {
                if(nodo->pElement == pElement)
                {
                    returnAux = i;
                    break;
                }
                nodo = nodo->pNextNode;
            }
        }
    }

    return returnAux;
}

/** \brief Indica si la lista esta o no vacia
 *
 * \param this LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 0) Si la lista NO esta vacia
                        ( 1) Si la lista esta vacia
 *
 */
int ll_isEmpty(LinkedList* this)
{
    int returnAux = -1;

    if(this != NULL)
    {
        if( ll_len(this))
        {
            returnAux = 0;
        }
        else
        {
            returnAux = 1;
        }
    }
    return returnAux;
}

/** \brief Inserta un nuevo elemento en la lista en la posicion indicada
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion donde se agregara el nuevo elemento
 * \param pElement void* Puntero al nuevo elemento
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                        ( 0) Si funciono correctamente
 *
 */
int ll_push(LinkedList* this, int index, void* pElement)
{
    int returnAux = -1;

    if(this != NULL && index >= 0 && index <= ll_len(this))
    {
        returnAux = addNode(this,index,pElement);
    }

    return returnAux;
}


/** \brief Elimina el elemento de la posicion indicada y retorna su puntero
 *
 * \param this LinkedList* Puntero a la lista
 * \param nodeIndex int Ubicacion del elemento eliminar
 * \return void* Retorna    (NULL) Error: si el puntero a la lista es NULL o (si el indice es menor a 0 o mayor al len de la lista)
                            (pElement) Si funciono correctamente
 *
 */
void* ll_pop(LinkedList* this,int index)
{
    void* returnAux = NULL;
    Node* nodo = NULL;

    if(this !=  NULL && index >= 0 && index <= ll_len(this))
    {
        nodo = getNode(this,index);
        if(nodo != NULL)
        {
            ll_remove(this,index);
            returnAux = nodo->pElement;
        }
    }

    return returnAux;
}


/** \brief  Determina si la lista contiene o no el elemento pasado como parametro
 *
 * \param this LinkedList* Puntero a la lista
 * \param pElement void* Puntero del elemento a verificar
 * \return int Retorna  (-1) Error: si el puntero a la lista es NULL
                        ( 1) Si contiene el elemento
                        ( 0) si No contiene el elemento
*/
int ll_contains(LinkedList* this, void* pElement)
{
    int returnAux = -1;

    if(this != NULL)
    {
        if(ll_indexOf(this,pElement)!= -1)
        {
            returnAux = 1;
        }
        else
        {
            returnAux = 0;
        }

    }

    return returnAux;
}

/** \brief  Determina si todos los elementos de la lista (this2)
            estan contenidos en la lista (this)
 *
 * \param this LinkedList* Puntero a la lista
 * \param this2 LinkedList* Puntero a la lista
 * \return int Retorna  (-1) Error: si alguno de los punteros a las listas son NULL
                        ( 1) Si los elementos de (this2) estan contenidos en la lista (this)
                        ( 0) si los elementos de (this2) NO estan contenidos en la lista (this)
*/
int ll_containsAll(LinkedList* this,LinkedList* this2)
{
    int returnAux = -1;

    if(this != NULL && this2 != NULL)
    {
        returnAux = 0;
        for(int i = 0; i < ll_len(this2); i++)
        {
            if(ll_contains(this,ll_get(this2,i)))
            {
                returnAux = 1;
            }
            else
            {
                returnAux = 0;
                break;
            }
        }
    }

    return returnAux;
}

/** \brief Crea y retorna una nueva lista con los elementos indicados
 *
 * \param pList LinkedList* Puntero a la lista
 * \param from int Indice desde el cual se copian los elementos en la nueva lista
 * \param to int Indice hasta el cual se copian los elementos en la nueva lista (no incluido)
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                o (si el indice from es menor a 0 o mayor al len de la lista)
                                o (si el indice to es menor o igual a from o mayor al len de la lista)
                         (puntero a la nueva lista) Si ok
*/
LinkedList* ll_subList(LinkedList* this,int from,int to)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL && from >= 0 && from < ll_len(this) && to>from && to <= ll_len(this))
    {
        cloneArray = ll_newLinkedList();
        for( ; from < to ; from++)
        {
            ll_add(cloneArray,ll_get(this,from));
            cloneArray->size++;
        }
    }
    return cloneArray;
}



/** \brief Crea y retorna una nueva lista con los elementos de la lista pasada como parametro
 *
 * \param pList LinkedList* Puntero a la lista
 * \return LinkedList* Retorna  (NULL) Error: si el puntero a la listas es NULL
                                (puntero a la nueva lista) Si ok
*/
LinkedList* ll_clone(LinkedList* this)
{
    LinkedList* cloneArray = NULL;

    if(this != NULL){
        //cloneArray = ll_newLinkedList();
        //cloneArray = this;
        cloneArray = ll_subList(this,0,ll_len(this));
    }

    return cloneArray;
}


/** \brief Ordena los elementos de la lista utilizando la funcion criterio recibida como parametro
 * \param pList LinkedList* Puntero a la lista
 * \param pFunc (*pFunc) Puntero a la funcion criterio
 * \param order int  [1] Indica orden ascendente - [0] Indica orden descendente
 * \return int Retorna  (-1) Error: si el puntero a la listas es NULL
                                ( 0) Si ok
 */
int ll_sort(LinkedList* this, int (*pFunc)(void*,void*), int order)
{
    int returnAux =-1;
    int flag;
    //void* pAux;
    void* auxElemento;
    void* auxElemento2;

    if(this != NULL && pFunc != NULL && (order == 0 || order == 1))
    {
    do{
        flag = 0;
            //printf("TAMAÑO DEL THIS: %d\n",ll_len(this));
            for(int i = 0 ; i < ll_len(this)-1;i++){
                auxElemento = ll_get(this,i);
                auxElemento2 = ll_get(this,i+1);
                if((pFunc(auxElemento,auxElemento2)>0 && order) || (pFunc(auxElemento,auxElemento2)<0 && !order)){
                        ll_set(this,i,auxElemento2);
                        ll_set(this,i+1,auxElemento);
                        flag = 1;
                        //printf("ENTRO %d\n",flag);
                }
            }
    }while(flag != 0);
        //printf("Salgo del WHILE\n");
        returnAux = 0;
    }

    return returnAux;

}

