if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_5) != (uint32_t)GPIO_PIN_RESET){
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 1);
	}
	else {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
	}
	
	if (HAL_GPIO_ReadPin(GPIOC, GPIO_PIN_6) != (uint32_t)GPIO_PIN_RESET){
	    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 1);
		}
	else {
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, 0);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_7, 0);
	}