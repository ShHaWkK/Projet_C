/**********************************************************************/
/* File : audio.h */
/* Date : 06/12/2023 */
/* author : ShHaWkK */
/**********************************************************************/

#ifndef AUDIO_H
#define AUDIO_H

#include "include.h"
//--------  --------//
void Audio_Init(const char* musicFilePath, const char* clickSoundFilePath);
void Audio_PlayMusic();
void Audio_PlayClickSound();
void Audio_Shutdown();

#endif // AUDIO_H
