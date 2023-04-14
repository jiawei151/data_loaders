// #include "/usr/include/eigen3/Eigen/Core"
// #include "/usr/include/eigen3/Eigen/Geometry"
// #include "/usr/include/eigen3/Eigen/StdVector"
// // #include "cpython/initconfig.h"

// #include "Python.h"

// #include "/workspace/data_loaders/deps/cnpy/cnpy.h"
// #include "/opt/conda/lib/python3.8/site-packages/numpy/core/include/numpy/arrayobject.h"
// // #include "eigen_utils.h"

// // https://codereview.stackexchange.com/questions/92266/sending-a-c-array-to-python-numpy-and-back/92353#92353

// int main(int argc, char *argv[]) {
//     std::string m_dataset_path = "/data/permuto_sdf_data/refnerf";
//     std::string m_restrict_to_scene_name = "coffee";
//     std::string mesh_file = m_dataset_path+ "/" + m_restrict_to_scene_name + "/points_of_interest.ply";
//     Py_Initialize();
//     PyRun_SimpleString("import sys; sys.path.insert(0, '/workspace/data_loaders/python')");
//     PyObject *pModule,*pFunc;
//     PyObject *pArgs, *pValue;
//     // pModule = PyImport_Import(PyUnicode_FromString("get_ply"));
//     pModule = PyImport_ImportModule("get_ply");
//     if (pModule == NULL) {
//         printf("ERROR importing module");
//         exit(-1);
//     } 
//     // PyObject* pModule = PyImport_ImportModule("my_module");
//     pFunc = PyObject_GetAttrString(pModule, "get_scale_mat");
//     if (pFunc == NULL) {
//         printf("ERROR importing func");
//         exit(-1);
//     } 
//     if (!PyCallable_Check(pFunc))
//         PyErr_Print();
//     pArgs = PyTuple_Pack(1, PyUnicode_FromString(mesh_file.c_str()));
//     pValue = PyObject_CallObject(pFunc, pArgs);
//     // pValue = PyObject_CallFunctionObjArgs(pFunc, pArgs);
//     if (pValue == NULL) {
//         printf("ERROR return");
//         exit(-1);
//     } 
//     PyArrayObject *np_ret = reinterpret_cast<PyArrayObject*>(pValue);

//     // Convert back to C++ array and print.
//     int len = PyArray_SHAPE(np_ret)[0];
//     float* scale_array_data = reinterpret_cast<float*>(PyArray_DATA(np_ret));

//     Eigen::Affine3f S_tmp;
//     Eigen::Affine3d S, S_test;
//     S_tmp.matrix() = Eigen::Map<Eigen::Matrix<float,4,4,Eigen::RowMajor> >(scale_array_data);
//     S=S_tmp.cast<double>();


//     // cnpy::NpyArrayPyObject scale_array = pValue;
//     // // cnpy::NpyArray scale_array = PyFloat_AsDouble(pValue);
//     // double* scale_array_data = scale_array.data<double>();

//     S_tmp.linear().col(2)=-S_tmp.linear().col(2); //make it look in the correct direction (the z vector of the frame should point towards the image frame)
//     S_tmp.linear().col(1)=-S_tmp.linear().col(1);

//     Py_DECREF(pModule);
//     Py_DECREF(pFunc);
//     Py_DECREF(pArgs);
//     Py_DECREF(pValue);
//     if (Py_FinalizeEx() < 0) {
//         exit(120);
//     }
//     // std::cout << "Hello, world!" << std::endl;

//     return 0;
// }



#include <bits/stdc++.h>
#include "/workspace/data_loaders/include/happly.h"


int main(){
    // Construct a data object by reading from file
    happly::PLYData plyIn("/data/permuto_sdf_data/refnerf/helmet/points_of_interest.ply");
    std::vector<std::array<double, 3>> vPos = plyIn.getVertexPositions();
    double bbox_xmax, bbox_ymax, bbox_zmax;
    double bbox_xmin, bbox_ymin, bbox_zmin;
    double center_x, center_y, center_z;
    double radius;
    bbox_xmax = -1000; bbox_ymax = -1000; bbox_zmax = -1000; bbox_xmin = 1000; bbox_ymin = 1000; bbox_zmin = 1000;
    for (int i=0; i<vPos.size(); i++){
        if (vPos[i][0] > bbox_xmax){
            bbox_xmax = vPos[i][0];
        }
        if (vPos[i][0] < bbox_xmin){
            bbox_xmin = vPos[i][0];
        }
        if (vPos[i][1] > bbox_ymax){
            bbox_ymax = vPos[i][1];
        }
        if (vPos[i][1] < bbox_ymin){
            bbox_ymin = vPos[i][1];
        }
        if (vPos[i][2] > bbox_zmax){
            bbox_zmax = vPos[i][2];
        }
        if (vPos[i][2] < bbox_zmin){
            bbox_zmin = vPos[i][2];
        }
    }
    center_x = (bbox_xmax+bbox_xmin) * 0.5;
    center_y = (bbox_ymax+bbox_ymin) * 0.5;
    center_z = (bbox_zmax+bbox_zmin) * 0.5;
    radius = -1000;
    for (int i=0; i<vPos.size(); ++i){
        double radiusi = std::sqrt((vPos[i][0]-center_x)*(vPos[i][0]-center_x)+(vPos[i][1]-center_y)*(vPos[i][1]-center_y)+(vPos[i][2]-center_z)*(vPos[i][2]-center_z));
        if (radiusi > radius){
            radius = radiusi;
        }
    }
    std::cout << center_x << " " << center_y << " " << center_z << " " << radius << std::endl;
    return 0;
}
