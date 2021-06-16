/*!
 * Copyright (c) 2021 SWTube. All rights reserved.
 * Licensed under the GPL-3.0 License. See LICENSE file in the project root for license information.
 */

#include "NeuralNetwork/NeuralNetwork.h"

namespace cave
{
	MemoryPool NeuralNetwork::msPool(1048576ul);

	NeuralNetwork::NeuralNetwork()
	{
		// LOGDF(eLogChannel::AI, "TensorFlow C library version %s", TF_Version());
	}

	void NeuralNetwork::DeallocateTensor(void* data, std::size_t size, void*) {
		msPool.Deallocate(data, size);
	}
	
#if CAVE_BUILD_DEBUG
	namespace NeuralNetworkTest
	{
		void Test()
		{
			OpenNN::DataSet dataSet("/home/alegruz/SWTube/Darkest-Cave/CaveEngine/AI/Data/iris_plant_original.csv", ';', true);

			const Tensor<string, 1> inputsName = dataSet.get_input_variables_names();
			const Tensor<string, 1> targetsNames = dataSet.get_target_variables_names();

			dataSet.split_samples_random();

			const Index inputVariablesNumber = dataSet.get_input_variables_number();
			const Index targetVariablesNumber = dataSet.get_target_variables_number();

			Tensor<string, 1> scalingInputsMethods(inputVariablesNumber);
			scalingInputsMethods.setConstant("MinimumMaximum");
			const Tensor<OpenNN::Descriptives, 1> inputsDescriptives = dataSet.scale_input_variables(scalingInputsMethods);

			Tensor<Index, 1> architecture(3);
			const Index hiddenNeuronsNumber = 3;
			architecture.setValues({inputVariablesNumber, hiddenNeuronsNumber, targetVariablesNumber});

			OpenNN::NeuralNetwork neuralNetwork(OpenNN::NeuralNetwork::Classification, architecture);

			neuralNetwork.set_inputs_names(inputsName);
			neuralNetwork.set_outputs_names(targetsNames);

			OpenNN::ScalingLayer* scalingLayerPointer = neuralNetwork.get_scaling_layer_pointer();
			scalingLayerPointer->set_descriptives(inputsDescriptives);
			scalingLayerPointer->set_scaling_methods(OpenNN::ScalingLayer::MinimumMaximum);

			OpenNN::TrainingStrategy trainingStrategy(&neuralNetwork, &dataSet);
			trainingStrategy.set_loss_method(OpenNN::TrainingStrategy::NORMALIZED_SQUARED_ERROR);
			trainingStrategy.set_optimization_method(OpenNN::TrainingStrategy::ADAPTIVE_MOMENT_ESTIMATION);
			trainingStrategy.perform_training();

			OpenNN::AdaptiveMomentEstimation* adam = trainingStrategy.get_adaptive_moment_estimation_pointer();
			adam->set_loss_goal(1.0e-3);
			adam->set_maximum_epochs_number(10000);
			adam->set_display_period(1000);
			trainingStrategy.perform_training();
			
			OpenNN::ModelSelection modelSelection(&trainingStrategy);
			modelSelection.perform_neurons_selection();

			dataSet.unscale_input_variables(scalingInputsMethods, inputsDescriptives);
			OpenNN::TestingAnalysis testingAnalysis(&neuralNetwork, &dataSet);
			Tensor<Index, 2> confusion = testingAnalysis.calculate_confusion();

			Tensor<OpenNN::type, 2> inputs(1, 4);
			inputs.setValues({{5.1, 3.5, 1.4, 0.2}});
			neuralNetwork.calculate_outputs(inputs);
			dataSet.unscale_input_variables(scalingInputsMethods, inputsDescriptives);

			neuralNetwork.save_expression_c("/home/alegruz/SWTube/Darkest-Cave/CaveEngine/AI/Data/expression.txt");
			// neuralNetwork.save_expression_python("/home/alegruz/SWTube/Darkest-Cave/CaveEngine/AI/Data/expression.txt");
		}
	} // namespace NeuralNetworkTest
	
#endif
} // namespace cave
