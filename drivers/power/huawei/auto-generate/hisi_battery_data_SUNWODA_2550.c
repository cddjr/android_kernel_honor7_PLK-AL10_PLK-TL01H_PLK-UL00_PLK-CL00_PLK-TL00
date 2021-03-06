
/* DO NOT EDIT - Generated automatically by build.py */

static struct single_row_lut SUNWODA_2550_fcc_temp = {
	.x		= {-20, -10, 0, 25, 40, 60},
	.y		= {2474, 2493, 2516, 2568, 2535, 2511},
	.cols	= 6
};

static struct single_row_lut SUNWODA_2550_fcc_sf = {
	.x		= {0, 100, 200, 300, 400, 500},
	.y		= {100, 96, 94, 92, 90, 88},
	.cols	= 6
};

static struct sf_lut SUNWODA_2550_pc_sf = {
	.rows = 1,
	.cols = 1,
	.row_entries = {0},
	.percent = {100},
	.sf = {
		{100}
	}
};


static struct sf_lut SUNWODA_2550_rbatt_sf = {
	.rows = 28,
	.cols = 6,
	.row_entries = {-20, -10, 0, 25, 40, 60},
	.percent = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
	.sf = {
		{1368, 639, 340, 149, 120, 111},
		{1368, 639, 340, 149, 120, 111},
		{1382, 674, 368, 159, 125, 112},
		{1377, 667, 390, 169, 130, 114},
		{1410, 666, 407, 180, 135, 117},
		{1401, 657, 419, 195, 142, 120},
		{1438, 656, 380, 210, 151, 125},
		{1474, 668, 366, 222, 165, 135},
		{1500, 690, 361, 186, 155, 135},
		{1539, 705, 362, 159, 130, 117},
		{1557, 729, 376, 159, 125, 114},
		{1608, 750, 391, 164, 127, 115},
		{1693, 768, 407, 170, 131, 118},
		{1786, 783, 417, 175, 138, 123},
		{1903, 805, 433, 174, 133, 115},
		{2061, 828, 448, 167, 127, 114},
		{2309, 825, 444, 164, 127, 114},
		{2746, 952, 423, 161, 126, 113},
		{3890, 1356, 506, 167, 127, 115},
		{4206, 1455, 516, 165, 130, 115},
		{4523, 1364, 507, 166, 128, 117},
		{3505, 1259, 509, 169, 127, 117},
		{3596, 1349, 530, 169, 129, 115},
		{4360, 1454, 556, 169, 126, 114},
		{5209, 1639, 582, 172, 127, 116},
		{6730, 2019, 651, 176, 130, 116},
		{9211, 2625, 771, 189, 135, 118},
		{13111, 3785, 1054, 356, 151, 124},
	}
};

static struct pc_temp_ocv_lut SUNWODA_2550_pc_temp_ocv = {
	.rows = 29,
	.cols = 6,
	.temp = {-20, -10, 0, 25, 40, 60},
	.percent = {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	.ocv = {
		{4329, 4328, 4325, 4319, 4311, 4303},
		{4249, 4257, 4257, 4256, 4249, 4244},
		{4183, 4198, 4199, 4200, 4194, 4189},
		{4122, 4136, 4143, 4145, 4140, 4136},
		{4070, 4080, 4090, 4093, 4089, 4086},
		{4011, 4026, 4041, 4046, 4042, 4039},
		{3961, 3976, 3983, 4001, 3999, 3997},
		{3918, 3932, 3938, 3958, 3959, 3958},
		{3878, 3894, 3899, 3909, 3912, 3913},
		{3843, 3859, 3864, 3868, 3870, 3871},
		{3807, 3832, 3837, 3841, 3842, 3842},
		{3777, 3809, 3814, 3819, 3820, 3820},
		{3756, 3790, 3796, 3800, 3802, 3801},
		{3740, 3774, 3780, 3785, 3786, 3785},
		{3727, 3760, 3768, 3769, 3768, 3759},
		{3715, 3745, 3756, 3752, 3745, 3734},
		{3702, 3715, 3734, 3730, 3724, 3712},
		{3687, 3690, 3699, 3700, 3692, 3679},
		{3656, 3667, 3671, 3674, 3670, 3659},
		{3648, 3662, 3666, 3671, 3666, 3656},
		{3640, 3657, 3662, 3666, 3663, 3652},
		{3631, 3648, 3655, 3660, 3656, 3646},
		{3613, 3634, 3644, 3646, 3643, 3630},
		{3590, 3611, 3622, 3618, 3612, 3597},
		{3554, 3573, 3584, 3575, 3569, 3554},
		{3502, 3519, 3531, 3519, 3514, 3501},
		{3433, 3447, 3461, 3446, 3444, 3433},
		{3340, 3351, 3366, 3350, 3347, 3340},
		{3200, 3200, 3200, 3200, 3200, 3200},
	}
};

struct hisi_smartstar_coul_battery_data SUNWODA_2550_battery_data = {
	.id_voltage_min = 1012,
	.id_voltage_max = 1212,
	.fcc = 2550,
	.fcc_temp_lut  = &SUNWODA_2550_fcc_temp,
	.fcc_sf_lut = &SUNWODA_2550_fcc_sf,
	.pc_temp_ocv_lut = &SUNWODA_2550_pc_temp_ocv,
	.pc_sf_lut = &SUNWODA_2550_pc_sf,
	.rbatt_sf_lut = &SUNWODA_2550_rbatt_sf,
	.default_rbatt_mohm = 100,
	.max_currentmA = 1000,
    .max_voltagemV = 4352,
    .max_cin_currentmA = 1200,
    .terminal_currentmA = 100,
    .charge_in_temp_5 = 3,
    .charge_in_temp_10 = 3,
    .batt_brand = "CHM-SUNWODA-2550",
};
