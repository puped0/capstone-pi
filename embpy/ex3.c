

#include <Python.h>

int main()
{
	Py_Initialize();
	PyRun_SimpleString("print('Hello World!')");
	Py_Finalize();

	return 0;
}
