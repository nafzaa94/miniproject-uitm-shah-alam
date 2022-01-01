if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 1){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
	}
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) == 0) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
	}

	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) == 0){
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
		}
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) == 1) {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
	}
