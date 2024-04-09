N = 3579545.0
factor = 1.0594631
base = 440.0

frequencies = []

BEFORE_A = 46
f = base
for i in range (BEFORE_A):
    idx = BEFORE_A - i - 1
    print(f"{idx}: {f}")
    frequencies.append(f)
    f = base / factor
    base = f
frequencies.reverse()

AFTER_A = 50
base = 440.0
for i in range(AFTER_A):
    idx = BEFORE_A + i
    f = base * factor
    print(f"{idx}: {f}")
    frequencies.append(f)
    base = f

# print(f"{frequencies}")

codes = []
for i in range(len(frequencies)):
    codes.append(round(N / (32.0 * frequencies[i])))


#const uint16_t frequencyCodes[8][12] = {
#  //    C,   Cis,     D,   Dis,     E,     F,   Fis,     G,   Gis,     A,   Ais,     H
#  { 06535, 06234, 05747, 05474, 05233, 05002, 04563, 04353, 04153, 03762, 03600, 03424 },  // Octave 1
#  { 03256, 03116, 02764, 02636, 02515, 02401, 02271, 02165, 02065, 01771, 01700, 01612 },  // Octave 2
#  { 01527, 01447, 01372, 01317, 01247, 01201, 01135, 01073, 01033, 00774, 00740, 00705 },  // Octave 3
#  { 00654, 00624, 00575, 00550, 00523, 00500, 00456, 00435, 00415, 00376, 00360, 00342 },  // Octave 4
#  { 00326, 00312, 00276, 00264, 00252, 00240, 00227, 00217, 00207, 00177, 00170, 00161 },  // Octave 5
#  { 00153, 00145, 00137, 00132, 00125, 00120, 00114, 00107, 00103, 00100, 00074, 00071 },  // Octave 6
#  { 00065, 00062, 00060, 00055, 00052, 00050, 00046, 00044, 00042, 00040, 00036, 00034 },  // Octave 7
#  { 00033, 00031, 00030, 00026, 00025, 00024, 00023, 00022, 00021, 00020, 00017, 00016 }   // Octave 8
#};



print("const uint16_t frequencyCodes[8][12] = {")
step = 12
for i in range(len(codes)):
    if (i % step == 0):
        print("  { ", end='')
    print(f"{codes[i]}", end='')
    if ((i+1) % step != 0):
        print(", ", end='')
    if ((i+1) % step == 0):
        print(" }", end='')
        if ((i+1) != len(codes)):
            print(", ")
        else:
            print()
print("};")



