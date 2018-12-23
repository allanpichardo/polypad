/******************************************************************************
 
 Copyright (c) 2015, Focusrite Audio Engineering Ltd.
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
 
 * Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.
 
 * Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution.
 
 * Neither the name of Focusrite Audio Engineering Ltd., nor the names of its
 contributors may be used to endorse or promote products derived from
 this software without specific prior written permission.
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 
 *****************************************************************************/

//______________________________________________________________________________
//
// Headers
//______________________________________________________________________________

#include "app.h"
#include "polypad.h"
#include "arpeggiator.h"

//______________________________________________________________________________
//
// This is where the fun is!  Add your code to the callbacks below to define how
// your app behaves.
//
// In this example, we either render the raw ADC data as LED rainbows or store
// and recall the pad state from flash.
//______________________________________________________________________________

// store ADC frame pointer
static const u16 *g_ADC = 0;
static u16 g_Ticks_ms = 150;
static u16 ms = 150;
static u8 g_Tempo_Blink = 0;
static u8 g_Note_Start = 60;

// buffer to store pad states for flash save
#define BUTTON_COUNT 100
u8 g_Buttons[BUTTON_COUNT] = {0};

//______________________________________________________________________________

void app_surface_event(u8 type, u8 index, u8 value)
{
    switch (type)
    {
        case  TYPEPAD:
        {
            if(value) {
                if(index == 40) {
                    polypad_quantize_down();
                }else if(index % 10 == 9) {
                    polypad_track_play_down(index);
                }else if(index == 91) {
                    polypad_uparrow_down(&g_Note_Start);
                }else if(index == 92) {
                    polypad_downarrow_down(&g_Note_Start);
                }else if(index == 93) {
                    polypad_leftarrow_down(&g_Ticks_ms);
                } else if(index == 94) {
                    polypad_rightarrow_down(&g_Ticks_ms);
                } else if(index == 70) {
                    polypad_click_down(polypad_ms_to_bpm(g_Ticks_ms));
                } else if(index > 10 && index < 89 && (index % 10) < 9 && (index % 10) > 0){
                    polypad_pad_down(index, &g_Note_Start);
                } else if(index == 8) {
                    polypad_stop_clip_down();
                }
            } else {
                if(index == 40) {
                    polypad_quantize_up();
                }else if(index % 10 == 9) {
                    polypad_track_play_up(index);
                }else if(index == 70) {
                    polypad_click_up();
                } else {
                    polypad_pad_up(index);
                }
            }
            // toggle it and store it off, so we can save to flash if we want to
//            if (value)
//            {
//                g_Buttons[index] = MAXLED * !g_Buttons[index];
//            }
//
//            // example - light / extinguish pad LEDs
//            hal_plot_led(TYPEPAD, index, 0, 0, g_Buttons[index]);
//
//            // example - send MIDI
//            hal_send_midi(DINMIDI, NOTEON | 0, index, value);
            
        }
        break;
            
        case TYPESETUP:
        {
            if (value)
            {
                // save button states to flash (reload them by power cycling the hardware!)
//                hal_write_flash(0, g_Buttons, BUTTON_COUNT);
            }
        }
        break;
    }
}

//______________________________________________________________________________

void app_midi_event(u8 port, u8 status, u8 d1, u8 d2)
{
    // example - MIDI interface functionality for USB "MIDI" port -> DIN port
    if (port == USBMIDI)
    {
        hal_send_midi(DINMIDI, status, d1, d2);
    }
    
    // // example -MIDI interface functionality for DIN -> USB "MIDI" port port
    if (port == DINMIDI)
    {
        hal_send_midi(USBMIDI, status, d1, d2);
    }
}

//______________________________________________________________________________

void app_sysex_event(u8 port, u8 * data, u16 count)
{
    // example - respond to UDI messages?
}

//______________________________________________________________________________

void app_aftertouch_event(u8 index, u8 value)
{
    // example - send poly aftertouch to MIDI ports
    hal_send_midi(USBMIDI, POLYAFTERTOUCH | 0, index, value);
    
    
}

//______________________________________________________________________________

void app_cable_event(u8 type, u8 value)
{
    // example - light the Setup LED to indicate cable connections
    if (type == MIDI_IN_CABLE)
    {
        hal_plot_led(TYPESETUP, 0, 0, value, 0); // green
    }
    else if (type == MIDI_OUT_CABLE)
    {
        hal_plot_led(TYPESETUP, 0, value, 0, 0); // red
    }
}

//______________________________________________________________________________

void app_timer_event()
{
    
    if (++ms >= g_Ticks_ms * 4)
    {
        ms = 0;
        
        // send a clock pulse up the USB
        hal_send_midi(USBSTANDALONE, MIDITIMINGCLOCK, 0, 0);
        hal_send_midi(USBMIDI, MIDITIMINGCLOCK, 0, 0);
        hal_send_midi(DINMIDI, MIDITIMINGCLOCK, 0, 0);
        
        //blink click button
        g_Tempo_Blink = !g_Tempo_Blink;
        if(g_Tempo_Blink) {
            hal_plot_led(TYPEPAD, 70, MAXLED, MAXLED, MAXLED);
        } else {
            hal_plot_led(TYPEPAD, 70, 0, 0, 0);
        }
        
        polypad_on_beat();
    }
    
    polypad_on_tick(&g_Note_Start, &g_Ticks_ms);
    
/*
	// alternative example - show raw ADC data as LEDs
	for (int i=0; i < PAD_COUNT; ++i)
	{
		// raw adc values are 12 bit, but LEDs are 6 bit.
		// Let's saturate into r;g;b for a rainbow effect to show pressure
		u16 r = 0;
		u16 g = 0;
		u16 b = 0;
		
		u16 x = (3 * MAXLED * g_ADC[i]) >> 12;
		
		if (x < MAXLED)
		{
			r = x;
		}
		else if (x >= MAXLED && x < (2*MAXLED))
		{
			r = MAXLED - x;
			g = x - MAXLED;
		}
		else
		{
			g = MAXLED - x;
			b = x - MAXLED;
		}
		
		hal_plot_led(TYPEPAD, ADC_MAP[i], r, g, b);
	}
 */
}

//______________________________________________________________________________

void app_init(const u16 *adc_raw)
{
    // example - load button states from flash
    //hal_read_flash(0, g_Buttons, BUTTON_COUNT);
    
    polypad_initialize_grid(&g_Ticks_ms);
	
	// store off the raw ADC frame pointer for later use
	g_ADC = adc_raw;
}
