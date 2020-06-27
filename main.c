#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "Controller.h"
#include "Employee.h"
#include <conio.h>
#include <ctype.h>
/****************************************************
    Menu:
     1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).
     2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).
     3. Alta de empleado
     4. Modificar datos de empleado
     5. Baja de empleado
     6. Listar empleados
     7. Ordenar empleados
     8. Guardar los datos de los empleados en el archivo data.csv (modo texto).
     9. Guardar los datos de los empleados en el archivo data.bin (modo binario).
    10. Salir
*****************************************************/

int menu();

int main()
{
    char rta = 'n';
    LinkedList* listaEmpleados = ll_newLinkedList();
    int flag = 0;
    int id = 1;

    if( listaEmpleados == NULL)
    {
        printf("No se pudo asignar memoria\n");
        system("pause");
        exit(EXIT_FAILURE);
    }

    do
    {
        switch(menu())
        {
        case 1:
            if(flag == 0)
            {
                if(controller_loadFromText("data.csv",listaEmpleados))
                {
                    idAutomatic(listaEmpleados,&id);
                    printf("[ - Empleados cargados con exito. - ]\n");
                }
                flag = 1;
            }
            else
            {
                printf("[ - Los empleados ya han sido cargados. - ]\n");
            }
            break;
        case 2:
            if(flag ==0)
            {
                if(controller_loadFromBinary("data.bin",listaEmpleados))
                {
                    idAutomatic(listaEmpleados,&id);
                    printf("[ - Empleados cargados con exito - ]\n");
                }
                flag = 1;
            }
            else
            {
                printf("[ - Los empleados ya han sido cargados. - ]\n");
            }
            break;
        case 3:
            idAutomatic(listaEmpleados,&id);

            if(controller_addEmployee(listaEmpleados,id) != 0)
            {
                printf("[ - Alta Exitosamente  - ]\n");
            }
            break;
        case 4:
            switch(controller_editEmployee(listaEmpleados))
            {
            case 1:
                printf("\n[ - Modificacion exitosa. - ]\n");
                break;
            case -1:
                printf("\n[ - Se cancelo la modificacion. - ]\n");
                fflush(stdin);
                break;
            default:
                printf("\n[ - Error. No se completo la modificacion o ID Incorrecto.- ]\n");
                fflush(stdin);
                break;
            }
            break;
        case 5:
            controller_removeEmployee(listaEmpleados);
            break;
        case 6:
            controller_ListEmployee(listaEmpleados);
            break;
        case 7:
            if(flag)
            {
                controller_sortEmployee(listaEmpleados);
            }
            else
            {
                printf("[ - No hay empleados cargados desde un archivo. - ]\n");
            }
            break;
        case 8:
            if(flag || id >= 1)
            {
                if(controller_saveAsText("data.csv",listaEmpleados))
                {
                    printf("[ - Empleados Guardados en modo texto con exito. - ]\n");
                }
            }
            else
            {
                printf("[ - No hay empleados cargados desde un archivo. - ]\n");
            }
            break;
        case 9:
            if(flag || id >= 1)
            {
                if(controller_saveAsBinary("data.bin",listaEmpleados))
                {
                    printf("[ - Empleados Guardados en modo binario con exito. - ]\n");
                }
            }
            else
            {
                printf("[ - No hay empleados cargados desde un archivo. - ]\n");
            }
            break;
        case 10:
            printf("Confirma salir?: (S/N) ");
            fflush(stdin);
            rta = getche();
            printf("\n\n");
            break;
        default:
            printf("[- Opcion Incorrecta - ]\n");
            break;
        }
        if(rta != 's')
        {
            system("pause");
            system("cls");
        }
        else
        {
            ll_deleteLinkedList(listaEmpleados);
            free(listaEmpleados);
        }

    }
    while(rta == 'n');
    return 0;
}

/** \brief  Menu Principal de Opciones
 * \param
 * \return int Opcion
 */

int menu()
{
    int opcion;

    printf("===========================================================================================\n");
    printf("[                  =======           MENU PRINCIPAL           =======                     ]\n");
    printf("===========================================================================================\n");
    printf("| 1. Cargar los datos de los empleados desde el archivo data.csv (modo texto).            |\n");
    printf("| 2. Cargar los datos de los empleados desde el archivo data.bin (modo binario).          |\n");
    printf("| 3. Alta de empleado.                                                                    |\n");
    printf("| 4. Modificar datos de empleado.                                                         |\n");
    printf("| 5. Baja de empleado.                                                                    |\n");
    printf("| 6. Listar empleados.                                                                    |\n");
    printf("| 7. Ordenar empleados.                                                                   |\n");
    printf("| 8. Guardar los datos de los empleados en el archivo data.csv (modo texto).              |\n");
    printf("| 9. Guardar los datos de los empleados en el archivo data.bin (modo binario).            |\n");
    printf("| 10. Salir.                                                                              |\n");
    printf("===========================================================================================\n");

    do
    {
        printf("Ingrese opcion: ");
        scanf("%d",&opcion);
        fflush(stdin);
    }
    while(isdigit(opcion) != 0);

    return opcion;
}
