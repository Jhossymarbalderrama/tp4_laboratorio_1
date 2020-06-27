#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Employee.h"
#include <conio.h>
#include <string.h>
#include <ctype.h>

/** \brief Busca ID Corrrespondiente para el Siguiente Empleado, ya sea por clientes cargador mediante un archivo CSV o BIN.
 *
 * \param pArrayListEmployee LinkedList*
 * \param id int*
 * \return int
 *
 */
int idAutomatic(LinkedList* pArrayListEmployee,int* id)
{
    int allOk = -1;
    Employee* filtro = NULL;
    int idAux = *id;

    if(pArrayListEmployee != NULL)
    {
        for(int i = 0; i < ll_len(pArrayListEmployee); i++)
        {
            filtro = (Employee*) ll_get(pArrayListEmployee,i);
            if(filtro->id == idAux && ll_len(pArrayListEmployee) != i)
            {
                idAux++;
            }
        }
        *id = idAux;
    }

    return allOk;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromText(char* path, LinkedList* pArrayListEmployee)
{
    int todoOk = 0;
    FILE* f;
    char buffer[4][100];
    int cant;

    Employee* aux = NULL;

    if(path != NULL && pArrayListEmployee != NULL)
    {
        f = fopen(path, "r");

        if( f == NULL)
        {
            printf("No se pudo abrir el archivo\n");
            return todoOk;
        }
        fscanf(f,"%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2],buffer[3]);

        while(!feof(f))
        {
            cant = fscanf(f,"%[^,],%[^,],%[^,],%[^\n]\n", buffer[0], buffer[1], buffer[2],buffer[3]);
            if( cant == 4)
            {
                aux = employee_newParametros(buffer[0], buffer[1], buffer[2],buffer[3]);
                if( aux != NULL)
                {
                    ll_add(pArrayListEmployee,aux);
                }
            }
            else
            {
                break;
            }
        }

        todoOk = 1;
    }

    return todoOk;
}

/** \brief Carga los datos de los empleados desde el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_loadFromBinary(char* path, LinkedList* pArrayListEmployee)
{
    int todoOk = 0;
    FILE* f;
    int cant;
    Employee* aux = NULL;

    if(path != NULL && pArrayListEmployee != NULL)
    {

        f = fopen(path, "rb");

        if( f == NULL)
        {
            printf("No se pudo abrir el archivo\n");
            return todoOk;
        }


        while(!feof(f))
        {
            aux = employee_new();
            if(aux != NULL)
            {
                cant =  fread( aux, sizeof(Employee),    1,  f );

                if(cant == 1)
                {
                    ll_add(pArrayListEmployee,aux);
                }

            }
            else
            {
                break;
            }
        }
        fclose(f);
        todoOk = 1;
    }

    return todoOk;
}

/** \brief Verifica una cadena, si es todo caracteres
 *
 * \param cadena char*
 * \return int
 *
 */
int isChar(char* cadena)
{
    int allOk = -1;
    int len = strlen(cadena);

    for(int i = 0 ; i < len; i++)
    {
        if(isalpha(cadena[i]))
        {
            allOk = 0;
        }
        else
        {
            allOk = -1;
            break;
        }
    }

    return allOk;
}

/** \brief Verifica una cadena, que sea todo Numericos
 *
 * \param cadena char*
 * \return int
 *
 */
int isdigitos(char* cadena)
{
    int allOk = -1;
    int len = strlen(cadena);

    for(int i = 0 ; i < len; i++)
    {
        if(isdigit(cadena[i]))
        {
            allOk = 0;
        }
        else
        {
            allOk = -1;
            break;
        }
    }

    return allOk;
}

/** \brief Pasa un valor Int a una Cadena del tipo Char[]
 *
 * \param numero unsigned longlong
 * \param bufer char*
 * \return void
 *
 */
void enteroACadena(unsigned long long numero, char *bufer)
{
    // Recuerda: llu es para un long long unsigned
    sprintf(bufer, "%llu", numero);
}


/** \brief Alta de empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_addEmployee(LinkedList* pArrayListEmployee,int id)
{
    int todoOk = 0;
    char buffer[4][20];

    if(pArrayListEmployee != NULL)
    {

        printf("[     =======     ALTA DE EMPLEADO     =======     ]\n\n");
        printf("ID: %d\n",id);
        enteroACadena(id,buffer[0]);

        printf("Ingrese nombre: ");
        fflush(stdin);
        gets(buffer[1]);
        while(isChar(buffer[1]) != 0)
        {
            printf("[ERROR]. Reingrese Nombre: ");
            fflush(stdin);
            gets(buffer[1]);
        }

        printf("Ingrese horas trabajadas: ");
        fflush(stdin);
        gets(buffer[2]);
        while(isdigitos(buffer[2]) != 0)
        {
            printf("[ERROR]. Reingrese horas trabajadas: ");
            fflush(stdin);
            gets(buffer[2]);
        }

        printf("Ingrese Sueldo: ");
        fflush(stdin);
        gets(buffer[3]);
        while(isdigitos(buffer[3]) != 0)
        {
            printf("[ERROR]. Reingrese Sueldo: ");
            fflush(stdin);
            gets(buffer[3]);
        }

        ll_add(pArrayListEmployee,employee_newParametros(buffer[0],buffer[1],buffer[2],buffer[3]));

        todoOk = 1;

    }

    return todoOk;
}

/** \brief  Menu Modificaciones de Empleado
 * \param
 * \return int opcion
 */

int menuModificacion()
{
    int opcion;

    printf("[   =======   MENU MODIFICACION DE EMPLEADO   =======   ]\n\n");
    printf("=======================================================\n");
    printf("1- Modificar Nombre.\n");
    printf("2- Modificar Horas de Trabajo.\n");
    printf("3- Modificar Sueldo.\n");
    printf("4. <-- Volver.\n");
    printf("=======================================================\n");
    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%d",&opcion);

    return opcion;
}


/** \brief Modificar datos de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_editEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk = 0;
    char rta = 'n';
    char buffer[1][20];
    Employee* filtro = NULL;
    char flagFor = 'n';
    int flagEdit = 0;
    char nuevoNombre[30];
    int nuevasHoras;
    int nuevoSueldo;

    if(pArrayListEmployee != NULL)
    {
        system("cls");
        printf("[     =======     MODIFICACION DE EMPLEADO     =======     ]\n\n");
        printf("=======================================================\n");

        printf("Ingrese ID: ");
        fflush(stdin);
        gets(buffer[0]);

        for(int i = 0; i<ll_len(pArrayListEmployee); i++)
        {
            filtro = (Employee*) ll_get(pArrayListEmployee,i);
            if(filtro->id == atoi(buffer[0]))
            {
                printf("\n   Id          Nombre   Horas Trabajadas   Sueldo\n\n");
                mostrarEmpleado(filtro);
                printf("=======================================================\n");
                printf("[ - Confirma Modificacion ? - ]  [ S / N ]\nElija opcion: ");

                flagFor = getchar();
                break;
            }
        }

        printf("=======================================================\n");
        if(flagFor == 's' || flagFor == 'S')
        {
            do
            {

                system("cls");
                printf("[     =======     MODIFICACION DE EMPLEADO     =======     ]\n\n");
                printf("=======================================================\n");
                printf("\n   Id          Nombre   Horas Trabajadas   Sueldo\n\n");
                mostrarEmpleado(filtro);
                printf("=======================================================\n");

                switch(menuModificacion())

                {
                case 1:
                    printf("Ingrese nuevo Nombre: ");
                    fflush(stdin);
                    gets(nuevoNombre);
                    while(isChar(nuevoNombre) != 0)
                    {
                        printf("[ERROR]. Reingrese el nuevo Nombre: ");
                        fflush(stdin);
                        gets(nuevoNombre);
                    }
                    strcpy(filtro->nombre,nuevoNombre);
                    flagEdit = 1;
                    break;
                case 2:
                    printf("Ingrese nueva cantidad de horas: ");
                    scanf("%d",&nuevasHoras);
                    while(nuevasHoras<0)
                    {
                        printf("ERROR. Las horas no pueden ser menores a cero. Reingrese:");
                        scanf("%d",&nuevasHoras);
                    }
                    filtro->horasTrabajadas = nuevasHoras;
                    flagEdit = 1;
                    break;
                case 3:
                    printf("Ingrese nuevo Sueldo: ");
                    scanf("%d",&nuevoSueldo);
                    while(nuevoSueldo<0)
                    {
                        printf("ERROR. El sueldo no puede ser menor a cero. Reingrese:");
                        scanf("%d",&nuevoSueldo);
                    }
                    filtro->sueldo = nuevoSueldo;
                    flagEdit = 1;
                    break;
                case 4:
                    printf("Confirma salir?: (S/N) ");
                    fflush(stdin);
                    rta = getche();
                    if(flagEdit == 0){
                        todoOk = -1;
                    }else{
                        todoOk = 1;
                    }
                    break;
                default:
                    printf("[ - Opcion invalida. - ]\n");
                    system("pause");
                    break;
                }
            }while(rta == 'n');
        }else{
            todoOk = -1;
        }
    }

    return todoOk;
}


/** \brief Baja de empleado
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_removeEmployee(LinkedList* pArrayListEmployee)
{

    int todoOk = 0;
    char buffer[1][20];
    Employee* filtro = NULL;
    int flagFor = 0;
    int indice;

    if(pArrayListEmployee != NULL)
    {

        system("cls");
        printf("[     =======     BAJA DE EMPLEADO     =======     ]\n\n");
        printf("Ingrese ID:");
        fflush(stdin);
        gets(buffer[0]);
        for(int i = 0; i<ll_len(pArrayListEmployee); i++)
        {
            filtro = (Employee*) ll_get(pArrayListEmployee,i);
            if(filtro->id == atoi(buffer[0]))
            {
                printf("=======================================================\n");
                printf("   Id         Nombre   Horas Trabajadas   Sueldo\n\n");
                mostrarEmpleado(filtro);
                printf("=======================================================\n");
                printf("\n[ - Confirma Baja del Empleado? - ]\n[1 Baja /0 Cancelar Operacion]\nElija opcion:");
                scanf("%d",&flagFor);
                indice = i;
                break;

            }
        }

        if(flagFor == 1)
        {
            ll_remove(pArrayListEmployee,indice);
            printf("[ - Empleado dado de baja exitosamente - ]\n\n");
        }
        else
        {
            printf("[ - Se cancelo la operacion - ]\n\n");
        }
        todoOk = 1;

    }



    return todoOk;
}

/** \brief Listar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_ListEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk = 0;
    Employee* aux;
    int flag = 0;
    if(pArrayListEmployee != NULL)
    {
        printf("  ID          Nombre   Horas de Trabajo    Sueldo\n\n");
        for( int i=0; i < ll_len(pArrayListEmployee); i++)
        {
            aux = (Employee*) ll_get(pArrayListEmployee,i);
            mostrarEmpleado(aux);
            flag = 1;
        }
        if(flag == 0)
        {
            printf("No hay empleados cargados para mostrar\n");
        }

        todoOk = 1;
    }
    return todoOk;
}


/** \brief  Menu Ordenamiento de Empleados
 * \param
 * \return int opcion
 */
int menuOrdenamiento()
{

    int opcion;
    system("cls");
    printf("[   =======   MENU ORDENAMIENTO DE EMPLEADOS   =======   ]\n\n");
    printf("=======================================================\n");
    printf("1- Ordenar por ID.\n");
    printf("2- Ordenar por Nombre.\n");
    printf("3- Ordenar por Horas de Trabajo.\n");
    printf("4- Ordenar por Sueldo.\n");
    printf("5. <-- Volver.\n");
    printf("=======================================================\n");
    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%d",&opcion);

    return opcion;
}


/** \brief Ordenar empleados
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_sortEmployee(LinkedList* pArrayListEmployee)
{
    int todoOk = 0;
    char rta = 'n';
    int orden;

    do
    {
        switch(menuOrdenamiento())
        {
        case 1:
            /**< Por ID */
            printf("Ingrese la Forma de Ordenamiento:\n1 ascendente / 0 descendente: ");
            scanf("%d",&orden);
            ll_sort(pArrayListEmployee,employee_CompareById,orden);
            printf("Ordenamiento exitoso.\n");
            system("pause");
            break;
        case 2:
            /**< Por Nombre */
            printf("Ingrese la Forma de Ordenamiento:\n1 ascendente / 0 descendente: ");
            scanf("%d",&orden);
            ll_sort(pArrayListEmployee,employee_CompareByName,orden);
            printf("Ordenamiento exitoso.\n");
            system("pause");
            break;
        case 3:
            /**< Por Horas Trabajadas*/
            printf("Ingrese la Forma de Ordenamiento:\n1 ascendente / 0 descendente: ");
            scanf("%d",&orden);
            ll_sort(pArrayListEmployee,employee_CompareByHoras,orden);
            printf("Ordenamiento exitoso.\n");
            system("pause");
            break;
        case 4:
            /**< Por Sueldo */
            printf("Ingrese la Forma de Ordenamiento:\n1 ascendente / 0 descendente: ");
            scanf("%d",&orden);
            ll_sort(pArrayListEmployee,employee_CompareBySueldo,orden);
            printf("Ordenamiento exitoso.\n");
            system("pause");
            break;
        case 5:
            /**< Volder */
            printf("Confirma salir? [S / N]: ");
            fflush(stdin);
            rta = getche();
            printf("\n");
            break;
        default:
            printf("[ - Opcion Incorrecta. - ]\n");
            system("pause");
            break;
        }

    }
    while(rta == 'n');

    return todoOk;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo texto).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsText(char* path, LinkedList* pArrayListEmployee)
{

    int todoOk = 0;
    int cant;
    FILE* f;
    Employee* aux = NULL;

    if(pArrayListEmployee!= NULL && path != NULL )
    {

        f = fopen(path,"w");
        if(f == NULL)
        {
            return todoOk;
        }
        fprintf(f,"id,nombre,horasTrabajadas,sueldo\n");
        for(int i = 0; i < ll_len(pArrayListEmployee); i++)
        {
            aux = ll_get(pArrayListEmployee,i);
            cant = fprintf(f,"%d,%s,%d,%d\n",aux->id,aux->nombre,aux->horasTrabajadas,aux->sueldo);
            if(cant < 1)
            {
                return todoOk;
            }
        }
        fclose(f);
        todoOk = 1;
    }
    return todoOk;
}

/** \brief Guarda los datos de los empleados en el archivo data.csv (modo binario).
 *
 * \param path char*
 * \param pArrayListEmployee LinkedList*
 * \return int
 *
 */
int controller_saveAsBinary(char* path, LinkedList* pArrayListEmployee)
{
    int todoOk = 0;
    int cant;
    FILE* f;

    if(pArrayListEmployee!= NULL && path != NULL )
    {

        f = fopen(path,"wb");
        if(f == NULL)
        {
            return todoOk;
        }
        for(int i = 0; i < ll_len(pArrayListEmployee); i++)
        {
            cant = fwrite( ll_get(pArrayListEmployee,i), sizeof(Employee),   1, f);
            if(cant < 1)
            {
                return todoOk;
            }
        }
        fclose(f);
        todoOk = 1;
    }

    return todoOk;

}
