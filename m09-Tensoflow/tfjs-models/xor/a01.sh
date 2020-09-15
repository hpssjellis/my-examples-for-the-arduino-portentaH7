#!/bin/bash



tensorflowjs_converter  \
--input_format tfjs_layers_model \
--output_format tfjs_layers_model \
--quantize_uint16  \
--output_node_names logits,Bias \
./model.json \
./quantized_model
