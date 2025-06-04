#include "arm_compute/runtime/NEON/NEFunctions.h"
#include "arm_compute/core/TensorShape.h"
#include "arm_compute/core/Types.h"
#include "arm_compute/runtime/Tensor.h"
#include "arm_compute/runtime/Allocator.h"

#include <iostream>

using namespace arm_compute;

int main()
{
    // Define dimensions: input = 3, output = 2
    const TensorShape input_shape(3);
    const TensorShape weights_shape(2, 3); // (output, input)
    const TensorShape bias_shape(2);
    const TensorShape output_shape(2);

    // Create tensors
    Tensor input, weights, bias, output;

    // Allocate shapes and types
    input.allocator()->init(TensorInfo(input_shape, 1, DataType::F32));
    weights.allocator()->init(TensorInfo(weights_shape, 1, DataType::F32));
    bias.allocator()->init(TensorInfo(bias_shape, 1, DataType::F32));
    output.allocator()->init(TensorInfo(output_shape, 1, DataType::F32));

    // Create Fully Connected layer
    NEFullyConnectedLayer fc_layer;
    fc_layer.configure(&input, &weights, &bias, &output);

    // Allocate memory
    input.allocator()->allocate();
    weights.allocator()->allocate();
    bias.allocator()->allocate();
    output.allocator()->allocate();

    // Fill input, weights, bias manually
    float *input_ptr = reinterpret_cast<float *>(input.buffer());
    float *weights_ptr = reinterpret_cast<float *>(weights.buffer());
    float *bias_ptr = reinterpret_cast<float *>(bias.buffer());

    input_ptr[0] = 1.0f;
    input_ptr[1] = 2.0f;
    input_ptr[2] = 3.0f;

    weights_ptr[0] = 0.5f; weights_ptr[1] = 0.1f; weights_ptr[2] = -0.3f;
    weights_ptr[3] = -0.6f; weights_ptr[4] = 0.9f; weights_ptr[5] = 0.2f;

    bias_ptr[0] = 0.1f;
    bias_ptr[1] = -0.2f;

    // Run the FC layer
    fc_layer.run();

    // Print output
    float *output_ptr = reinterpret_cast<float *>(output.buffer());
    std::cout << "Output:" << std::endl;
    for (int i = 0; i < 2; ++i)
    {
        std::cout << output_ptr[i] << std::endl;
    }

    return 0;
}
