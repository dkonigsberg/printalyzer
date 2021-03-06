#include "pam8904e.h"

void pam8904e_set_gain(pam8904e_handle_t *handle, pam8904e_gain_t gain)
{
    HAL_GPIO_WritePin(handle->en1_gpio_port, handle->en1_gpio_pin,
        (gain & 0x02) ? GPIO_PIN_SET : GPIO_PIN_RESET);
    HAL_GPIO_WritePin(handle->en2_gpio_port, handle->en2_gpio_pin,
        (gain & 0x01) ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void pam8904e_set_frequency(pam8904e_handle_t *handle, pam8904e_freq_t freq)
{
    switch (freq) {
    case PAM8904E_FREQ_DEFAULT:
        __HAL_TIM_SET_PRESCALER(handle->din_tim, 0);
        __HAL_TIM_SET_AUTORELOAD(handle->din_tim, 65535);
        __HAL_TIM_SET_COMPARE(handle->din_tim, handle->din_tim_channel, 32767);
        break;
    case PAM8904E_FREQ_500HZ:
        __HAL_TIM_SET_PRESCALER(handle->din_tim, 2);
        __HAL_TIM_SET_AUTORELOAD(handle->din_tim, 63999);
        __HAL_TIM_SET_COMPARE(handle->din_tim, handle->din_tim_channel, 31999);
        break;
    case PAM8904E_FREQ_1000HZ:
        __HAL_TIM_SET_PRESCALER(handle->din_tim, 1);
        __HAL_TIM_SET_AUTORELOAD(handle->din_tim, 47999);
        __HAL_TIM_SET_COMPARE(handle->din_tim, handle->din_tim_channel, 23999);
        break;
    case PAM8904E_FREQ_1500HZ:
        __HAL_TIM_SET_PRESCALER(handle->din_tim, 0);
        __HAL_TIM_SET_AUTORELOAD(handle->din_tim, 63999);
        __HAL_TIM_SET_COMPARE(handle->din_tim, handle->din_tim_channel, 31999);
        break;
    case PAM8904E_FREQ_2000HZ:
        __HAL_TIM_SET_PRESCALER(handle->din_tim, 0);
        __HAL_TIM_SET_AUTORELOAD(handle->din_tim, 47999);
        __HAL_TIM_SET_COMPARE(handle->din_tim, handle->din_tim_channel, 23999);
        break;
    case PAM8904E_FREQ_4800HZ:
        __HAL_TIM_SET_PRESCALER(handle->din_tim, 0);
        __HAL_TIM_SET_AUTORELOAD(handle->din_tim, 19999);
        __HAL_TIM_SET_COMPARE(handle->din_tim, handle->din_tim_channel, 9999);
        break;
    default:
        break;
    }
}

void pam8904e_start(pam8904e_handle_t *handle)
{
    HAL_TIM_PWM_Start(handle->din_tim, handle->din_tim_channel);
}

void pam8904e_stop(pam8904e_handle_t *handle)
{
    HAL_TIM_PWM_Stop(handle->din_tim, handle->din_tim_channel);
}
