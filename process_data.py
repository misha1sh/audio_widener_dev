
import os
os.environ["PATH"] = 'C:\\conda\\envs\\ds;C:\\conda\\envs\\ds\\Library\\mingw-w64\\bin;C:\\conda\\envs\\ds\\Library\\usr\\bin;C:\\conda\\envs\\ds\\Library\\bin;C:\\conda\\envs\\ds\\Scripts;C:\\conda\\envs\\ds\\bin;C:\\conda\\condabin;C:\\Program Files\\Common Files\\Oracle\\Java\\javapath;C:\\Program Files (x86)\\Common Files\\Oracle\\Java\\javapath;C:\\conda;C:\\conda\\Library\\mingw-w64\\bin;C:\\conda\\Library\\usr\\bin;C:\\conda\\Library\\bin;C:\\conda\\Scripts;C:\\Windows\\system32;C:\\Windows;C:\\Windows\\System32\\Wbem;C:\\Windows\\System32\\WindowsPowerShell\\v1.0;C:\\Windows\\System32\\OpenSSH;C:\\Program Files (x86)\\NVIDIA Corporation\\PhysX\\Common;C:\\Program Files\\Intel\\WiFi\\bin;C:\\Program Files\\Common Files\\Intel\\WirelessCommon;D:\\downloads\\fasmw17325\\INCLUDE;C:\\Program Files (x86)\\QuickTime\\QTSystem;D:\\program_files\\Git\\cmd;D:\\program_files\\fasmw17325;D:\\program_files\\Oracle\\VirtualBox;D:\\program_files\\fasmw17325\\INCLUDE;D:\\program_files\\nodejs;C:\\Program Files\\dotnet;D:\\program_files\\PuTTY;D:\\program_files\\ffmpeg\\bin;D:\\program_files\\JUCE;C:\\Users\\user\\AppData\\Local\\Microsoft\\WindowsApps;C:\\Users\\user\\AppData\\Roaming\\npm;C:\\Users\\user\\.dotnet\\tools'  
import sys
sys.path = ['', 'C:\\conda\\python38.zip', 'C:\\conda\\DLLs', 'C:\\conda\\lib', 'C:\\conda', 'C:\\Users\\user\\AppData\\Roaming\\Python\\Python38\\site-packages', 'C:\\conda\\lib\\site-packages', 'C:\\conda\\lib\\site-packages\\win32', 'C:\\conda\\lib\\site-packages\\win32\\lib', 'C:\\conda\\lib\\site-packages\\Pythonwin'] 

import scipy.fft as fft
import scipy.signal as signal
print("f")
import numpy as np
import json5
import libpasteurize

import librosaf

from IPython.display import Audio, display
import pywt
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
import matplotlib.patches as mpatches



def split_into_bands(Zxx, numbands):
    # нужно сгенерировать таблицу бандов, в каждой ячейке -- номер банда
    mask = np.zeros(Zxx.shape)

    value_per_band = np.sum(np.abs(Zxx)) / numbands
#     value_per_band = Zxx.shape[0] // numbands
    value = 0
    band = 0

    for i, freq_line in enumerate(Zxx):
        cur_val = np.sum(np.abs(freq_line))
#         print(i, cur_val)
        if value < value_per_band:
            mask[i, :] = band
        else:
            mask[i, :] = band + 1
        value += cur_val
#         value += 1
        if value >= value_per_band:
            band += 1
        while value >= value_per_band:
            value -= value_per_band
    return mask


def m2s_freq_split(sound, sample_rate, numbands):
    global f, t, Zxx
    nperseg = 1024
    noverlap = 512

    f, t, Zxx = signal.stft(sound, sample_rate, nperseg=nperseg, noverlap=noverlap)
    Zxx1 = Zxx.copy()
    Zxx2 = Zxx.copy()
    mask = split_into_bands(Zxx, numbands)
    
    mask1 = mask % 2 == 0
    mask2 = mask % 2 == 1
    Zxx1[mask1] = 0
    Zxx2[mask2] = 0
#     for i in range(Zxx.shape[0]):
        
#         if i % 15 < 9:
#             Zxx1[i,:] = 0
#         else:
#             Zxx2[i,:] = 0
    _, sound1 = signal.istft(Zxx1, sample_rate, nperseg=nperseg, noverlap=noverlap)
    _, sound2 = signal.istft(Zxx2, sample_rate, nperseg=nperseg, noverlap=noverlap)
    
    return sound1, sound2

def dry_wet(sound, original, wet):
    return sound[:len(original)]*wet + original * (1 - wet)

def dry_wet_stereo(sound1, sound2, mono, wet):
    return dry_wet(sound1, mono, wet), dry_wet(sound2, mono, wet)

def method1(song, song_rate):
    global sound1, sound2
    sound1, sound2 = m2s_freq_split(song, song_rate, 100)
    sound1, sound2 = dry_wet_stereo(sound1, sound2, song, 1.0)
    return sound1, sound2
    
with open("test.txt", "w") as ttt:
    ttt.write("qwew")