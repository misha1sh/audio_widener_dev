from imports import *


def split_into_bands_static(Zxx, numbands):
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

def split_into_bands_log(Zxx, numbands):
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


def m2s_freq_split(sound, sample_rate, numbands, split_into_bands=split_into_bands_static):
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
    return sound[:len(original)] * wet + original * (1 - wet)


def dry_wet_stereo(sound1, sound2, mono, wet):
    return dry_wet(sound1, mono, wet), dry_wet(sound2, mono, wet)


# noinspection PyTypeChecker
def audio_mono_stereo(mono, sound1, sound2, sample_rate):
    print("stereo:")
    display(Audio([sound1, sound2], rate=sample_rate, autoplay=True, normalize=True))
    print("mono:")
    display(Audio(mono, rate=sample_rate, autoplay=False, normalize=True))

def method1(song, song_rate):
    global sound1, sound2
    sound1, sound2 = m2s_freq_split(song, song_rate, 10)
    sound1, sound2 = dry_wet_stereo(sound1, sound2, song, 0.8)
    audio_mono_stereo(song, sound1, sound2, song_rate)




# mask = split_into_bands(Zxx, 10)