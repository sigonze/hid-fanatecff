#ifndef __HID_FTEC_H
#define __HID_FTEC_H

#define FANATEC_VENDOR_ID 0x0eb7

#define CLUBSPORT_V2_WHEELBASE_DEVICE_ID 0x0001
#define CLUBSPORT_V25_WHEELBASE_DEVICE_ID 0x0004
#define PODIUM_WHEELBASE_DD1_DEVICE_ID 0x0006
#define CSL_ELITE_WHEELBASE_DEVICE_ID 0x0E03
#define CSL_ELITE_PS4_WHEELBASE_DEVICE_ID 0x0005
#define CSL_ELITE_PEDALS_DEVICE_ID 0x6204

#define FORUMLA1_IS_ID 0x1102
#define CSL_ELITE_WHEEL_WRC_ID 0x0112

#define LEDS 9
#define NUM_TUNING_SLOTS 5
#define FTECFF_MAX_EFFECTS 16

struct ftecff_effect_state {
	struct ff_effect effect;
	struct ff_envelope *envelope;
	unsigned long start_at;
	unsigned long play_at;
	unsigned long stop_at;
	unsigned long flags;
	unsigned long time_playing;
	unsigned long updated_at;
	unsigned int phase;
	unsigned int phase_adj;
	unsigned int count;
	unsigned int cmd;
	unsigned int cmd_start_time;
	unsigned int cmd_start_count;
	int direction_gain;
	int slope;
};

struct ftecff_effect_parameters {
	int level;
	int d1;
	int d2;
	int k1;
	int k2;
	unsigned int clip;
};

struct ftecff_slot {
	int id;
	struct ftecff_effect_parameters parameters;
	u8 current_cmd[7];
	int cmd_op;
	int is_updated;
	int effect_type;
};

struct ftec_drv_data {
	unsigned long quirks;
    spinlock_t report_lock; /* Protect output HID report */
	spinlock_t timer_lock;
	struct hrtimer hrtimer;
	struct hid_device *hid;
	struct hid_report *report;
	struct ftecff_slot slots[4];
	struct ftecff_effect_state states[FTECFF_MAX_EFFECTS];
	int effects_used;	
	u16 range;
	u16 max_range;
	u16 min_range;
#ifdef CONFIG_LEDS_CLASS
	u16 led_state;
	struct led_classdev *led[LEDS];
#endif    
};

#endif
