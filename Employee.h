#ifndef employee_H_INCLUDED
#define employee_H_INCLUDED
typedef struct
{
    int id;
    char nombre[128];
    int horasTrabajadas;
    int sueldo;
}Employee;

Employee* employee_new();
Employee* employee_newParametros(char* idStr,char* nombreStr,char* horasTrabajadasStr,char* sueldo);
void employee_delete();

int employee_setId(Employee* this,int id);
int employee_getId(Employee* this,int* id);

int employee_setNombre(Employee* this,char* nombre);
int employee_getNombre(Employee* this,char* nombre);

int employee_setHorasTrabajadas(Employee* this,int horasTrabajadas);
int employee_getHorasTrabajadas(Employee* this,int* horasTrabajadas);

int employee_setSueldo(Employee* this,int sueldo);
int employee_getSueldo(Employee* this,int* sueldo);


int mostrarEmpleado(Employee* e);

int employee_CompareById(void* e1,void* e2);
int employee_CompareByName(void* e1,void* e2);
int employee_CompareByHoras(void* e1,void* e2);
int employee_CompareBySueldo(void* e1,void* e2);

/**
    int sortById(void* empleado1,void* empleado2);
    int sortByName(void* empleado1,void* empleado2);
    int sortByHoras(void* empleado1,void* empleado2);
    int sortBySueldo(void* empleado1,void* empleado2);
*/

#endif // employee_H_INCLUDED

