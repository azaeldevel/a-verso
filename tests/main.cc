
#include <cstring>
#include <string>


#ifdef OCTETOS_AVERSO_V0_TESTING
	#include "v0.hh"
#endif


int main(int argc, char *argv[])
{
    std::string mode;
    for(int i = 0; i < argc; i++)
    {
        if(strcmp(argv[i], "--mode") == 0)
        {
            mode = argv[++i];
        }
    }

	/* initialize the CUnit test registry */
	if (CUE_SUCCESS != CU_initialize_registry()) return CU_get_error();

#ifdef OCTETOS_AVERSO_V0_TESTING
	CU_pSuite pSuite_v0 = CU_add_suite("Testing for Verso v0", v0_init, v0_clean);
	if (NULL == pSuite_v0)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite_v0, "Developing..", v0_developing)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite_v0, "Matematicas vectoriales..", v0_math)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite_v0, "Asegurando compatibilidad con OpenGL..", v0_opnegl_compatible)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite_v0, "Funciones y operadores C++..", v0_cpp_features)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if ((NULL == CU_add_test(pSuite_v0, "Asegurando compatibilidad con GLM..", v0_glm_compatible)))
	{
		CU_cleanup_registry();
		return CU_get_error();
	}


#endif

	/* Run all tests using the CUnit Basic interface */
	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}

