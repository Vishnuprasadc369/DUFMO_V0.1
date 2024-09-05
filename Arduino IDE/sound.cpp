#include "sound.h"
#include "soundData.h"
#include "driver/dac.h"
#define DAC_CHANNEL DAC_CHANNEL_1
void sound_eye(){
    const unsigned int soundDataLength = sizeof(eye_sound);
    for (unsigned int i = 0; i < soundDataLength; i++) {
    // Write each byte of the sound data to the DAC
    dac_output_voltage(DAC_CHANNEL, eye_sound[i]);
    
    // Delay to control the playback speed
    // Adjust this value based on the sample rate of your WAV file
    delayMicroseconds(125); // Example value for ~8kHz sample rate
  }

}
void sound_angry(){
    const unsigned int soundDataLength = sizeof(angry_sound);
    for (unsigned int i = 0; i < soundDataLength; i++) {
    // Write each byte of the sound data to the DAC
    dac_output_voltage(DAC_CHANNEL, angry_sound[i]);
    
    // Delay to control the playback speed
    // Adjust this value based on the sample rate of your WAV file
    delayMicroseconds(125); // Example value for ~8kHz sample rate
  }

}

void sound_sad(){
    const unsigned int soundDataLength = sizeof(sad_sound);
    for (unsigned int i = 0; i < soundDataLength; i++) {
    // Write each byte of the sound data to the DAC
    dac_output_voltage(DAC_CHANNEL, sad_sound[i]);
    
    // Delay to control the playback speed
    // Adjust this value based on the sample rate of your WAV file
    delayMicroseconds(125); // Example value for ~8kHz sample rate
  }

}
void sound_happy(){
    const unsigned int soundDataLength = sizeof(happy_sound);
    for (unsigned int i = 0; i < soundDataLength; i++) {
    // Write each byte of the sound data to the DAC
    dac_output_voltage(DAC_CHANNEL, happy_sound[i]);
    
    // Delay to control the playback speed
    // Adjust this value based on the sample rate of your WAV file
    delayMicroseconds(125); // Example value for ~8kHz sample rate
  }

}

void sound_left(){
    const unsigned int soundDataLength = sizeof(left_sound);
    for (unsigned int i = 0; i < soundDataLength; i++) {
    // Write each byte of the sound data to the DAC
    dac_output_voltage(DAC_CHANNEL, left_sound[i]);
    
    // Delay to control the playback speed
    // Adjust this value based on the sample rate of your WAV file
    delayMicroseconds(125); // Example value for ~8kHz sample rate
  }

}
void sound_doubt(){
    const unsigned int soundDataLength = sizeof(doubt_sound);
    for (unsigned int i = 0; i < soundDataLength; i++) {
    // Write each byte of the sound data to the DAC
    dac_output_voltage(DAC_CHANNEL, doubt_sound[i]);
    
    // Delay to control the playback speed
    // Adjust this value based on the sample rate of your WAV file
    delayMicroseconds(125); // Example value for ~8kHz sample rate
  }

}

void sound_hey(){
    const unsigned int soundDataLength = sizeof(hay_sound);
    for (unsigned int i = 0; i < soundDataLength; i++) {
    // Write each byte of the sound data to the DAC
    dac_output_voltage(DAC_CHANNEL, hay_sound[i]);
    
    // Delay to control the playback speed
    // Adjust this value based on the sample rate of your WAV file
    delayMicroseconds(125); // Example value for ~8kHz sample rate
  }

}


void sound_right(){
    const unsigned int soundDataLength = sizeof(right_sound);
    for (unsigned int i = 0; i < soundDataLength; i++) {
    // Write each byte of the sound data to the DAC
    dac_output_voltage(DAC_CHANNEL, right_sound[i]);
    
    // Delay to control the playback speed
    // Adjust this value based on the sample rate of your WAV file
    delayMicroseconds(125); // Example value for ~8kHz sample rate
  }

}