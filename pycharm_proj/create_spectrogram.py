from imports import *


def create_spectrogram(sound, sample_rate, mode):
    drawing_params = {
        "NFFT": 1024,#64, # 1024,
        "noverlap": 512,#412,#32, #512,
        "Fs": sample_rate
    }
    window = signal.windows.hann(drawing_params["NFFT"])
#     window = lambda x:x
    #mode = magnitude
#     drawing_params["freqs"], drawing_params["t"], Sxx = signal.stft(sound, window=window,
#                                                                     nfft=drawing_params["NFFT"],
#                                                                     nperseg=drawing_params["NFFT"],
#                                                                     noverlap=drawing_params["noverlap"],
#                                                                     fs=drawing_params["Fs"])
#     Sxx = np.abs(Sxx)

    Sxx, drawing_params["freqs"], drawing_params["t"] = mlab.specgram(sound, window=window, mode=mode, **drawing_params)
#     Sxx[Sxx<=0] = 0 # WARN!!!!!!!!!!!!!!!
    return Sxx, drawing_params


def log_scale(values):
    values = values.copy()
    values[values>0] = np.log10(values[values>0] * 100 + 1)
    values[values<0] = -np.log10(-values[values<0] * 100 + 1)

    return values

