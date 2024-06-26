/*  ---------------------------------------------------------------------------

    (c) copyright 2021 Altair Semiconductor, Ltd. All rights reserved.

    This software, in source or object form (the "Software"), is the
    property of Altair Semiconductor Ltd. (the "Company") and/or its
    licensors, which have all right, title and interest therein, You
    may use the Software only in  accordance with the terms of written
    license agreement between you and the Company (the "License").
    Except as expressly stated in the License, the Company grants no
    licenses by implication, estoppel, or otherwise. If you are not
    aware of or do not agree to the License terms, you may not use,
    copy or modify the Software. You may use the source code of the
    Software only for your internal purposes and may not distribute the
    source code of the Software, any part thereof, or any derivative work
    thereof, to any third party, except pursuant to the Company's prior
    written consent.
    The Software is the confidential information of the Company.

   ------------------------------------------------------------------------- */
#ifndef _CONFIG_H_
#define _CONFIG_H_

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular
 * application requirements.
 *----------------------------------------------------------*/

#define APPLICATION_VERSION "1.0.0"

#define configUSE_ALT_SLEEP 1

#define __ENABLE_MQTT_API_          /* MQTT Functionility */
#define __ENABLE_AWS_API__          /* AWS Connectivity */
#define __ENABLE_CERTMGMT_API__     /* Certificate Management */

#define WE_MICROSECOND_TICK 1


#endif /* _CONFIG_H_ */
