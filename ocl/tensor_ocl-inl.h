#ifndef MLITE_OCL_TENSOR_INL_H_
#define MLITE_OCL_TENSOR_INL_H_
#include "../base.h"
#include "../tensor.h"
#include "executor.h"
namespace mlite {
static cl_device_id kOclDefualtDeviceId = 0;
template<>
MLITE_XINLINE void InitTensorEngine<ocl>(int dev_id) {
	Executor::Get()->SetDevice(&dev_id);
}
template<>
MLITE_XINLINE void ShutdownTensorEngine<ocl>(void) {
	Executor::Get()->ReleaseDevice();
}
template<>
MLITE_XINLINE void SetDevice<ocl>(int devid) {
	Executor::Get()->SetDevice(&dev_id);
}
template<>
inline Stream<cpu> *NewStream<ocl>(bool create_blas_handle,
	bool create_dnn_handle) {
	return new Stream<ocl>();
}
template<>
MLITE_XINLINE void DeleteStream<ocl>(Stream<ocl> *stream) {
	delete stream;
}
template<typename DType>
MLITE_XINLINE void AllocSpace(Tensor<ocl, DType> *obj) {
	cl_int err;
	cl_context context = Executor::GetContext();
	obj->set_cl_data(clCreateBuffer(
		context, CL_MEM_READ_WRITE, obj->size() * sizeof(DType), NULL, &err));
	CHECK_NE(err, CL_FALSE) << "Error allocting device memory!";
}
template<typename DType>
MLITE_XINLINE void FreeSpace(Tensor<cpu, DType> *obj) {
	free(obj->data());
}
inline void CheckLaunchParam() {}
}

#endif // ! MLITE_OCL_TENSOR_INL_H_