/**
 *******************************************************************************
 * @file           : common_def.h
 * @brief          : Common Definitions
 * @version        : 1.0
 *******************************************************************************
*/

#ifndef __COMMON_DEF_H
#define __COMMON_DEF_H

#ifdef __cplusplus
extern "C"
{
#endif

#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
  #ifndef __weak
    #define __weak  __attribute__((weak))
  #endif
  #ifndef __packed
    #define __packed  __attribute__((packed))
  #endif
#elif defined ( __GNUC__ ) && !defined (__CC_ARM) /* GNU Compiler */
  #ifndef __weak
    #define __weak   __attribute__((weak))
  #endif /* __weak */
  #ifndef __packed
    #define __packed __attribute__((__packed__))
  #endif /* __packed */
#endif /* __GNUC__ */

typedef enum{
	Env_Result_OK = 0,
	Env_Result_ERROR
}Env_Result_t;


#ifdef __cplusplus
}
#endif

#endif /* __CIRCULAR_BUFFER_H */
