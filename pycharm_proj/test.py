from imports import *




nperseg = 32
noverlap = 16
guitar_sample, guitar_sample_rate = librosa.load("samples/guitar.wav")
f, t, Zxx = signal.stft(guitar_sample[:100], guitar_sample_rate, nperseg=nperseg, noverlap=noverlap)


_, sound1 = signal.istft(Zxx, guitar_sample_rate, nperseg=nperseg, noverlap=noverlap)