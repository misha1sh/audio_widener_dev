from imports import *


def gen_sine_weights(cnt=30):
    x = np.linspace(0, np.pi, cnt)
    y = x

    weights = np.zeros((len(x), len(y)))
    for i in range(len(x)):
        for j in range(len(y)):
            weights[i][j] = np.sin(x[i]) * np.sin(y[j])
    weights = weights / np.sum(weights[:])
    return weights



def split_into_bands_by_volume(numbands):
    def __func(Zxx):
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
        return mask % 2
    return __func


def split_into_bands_perlin_noise(xstretch, ystretch):
    ret

def split_into_bands_by_random_horizontal(stretch=20):
    def __func(Zxx):
        from random import random
        random_val = random()
        mask = np.zeros(Zxx.shape)
        for i in range(mask.shape[0]):
            random_val = 1 - random_val
            for j in range(mask.shape[1]):
                mask[i][j] = random_val
                random_val += (random() - 0.5) / stretch * 10
                if random_val < 0: random_val = 0
                if random_val > 1: random_val = 1
        return mask

    return __func


def apply_horizontal_split(mask, dynamic_time_period=20):
    per_time = dynamic_time_period
    for j in range(int(np.ceil(mask.shape[1] / per_time))):
        if j % 2 == 0:
            mask[:, j * per_time:j * per_time + per_time] = 1 - mask[:, j * per_time:j * per_time + per_time]
    return mask


def split_into_bands_by_parts():
    def __func(Zxx):
        # нужно сгенерировать таблицу бандов, в каждой ячейке -- номер банда
        mask = np.zeros(Zxx.shape)

        cur_limit = 1  # np.log2(Zxx.shape[0])
        band = 0

        for i, freq_line in enumerate(Zxx):
            if i >= cur_limit:
                cur_limit *= 2
                band += 1
            # if is_dynamic:
            #     per_time = dynamic_time_period
            #     for j in range(int(np.ceil(Zxx.shape[1] / per_time))):
            #         mask[i, j * per_time:j * per_time + per_time] = band + j
            # else:
            mask[i, :] = band
        mask %= 2
        return mask

    return __func

def apply_convolution_to_mask(mask, type="sin", strength=30):
    if type == "sin":
        return ndfilters.convolve(mask, gen_sine_weights(strength), mode='constant')
    elif type == "gaussian":
        return ndfilters.gaussian_filter(mask, sigma=strength/4)
    raise Exception("Unknown type: " + str(type))

def m2s_with_mask(sound, sample_rate, split_into_bands=split_into_bands_by_parts()):
    global f, t, Zxx
    nperseg = 1024
    noverlap = 512

    f, t, Zxx = signal.stft(sound, sample_rate, nperseg=nperseg, noverlap=noverlap)
    mask = split_into_bands(Zxx)

    Zxx1 = Zxx * mask
    Zxx2 = Zxx * (1 - mask)

    # mask1 = mask % 2 == 0
    # mask2 = mask % 2 == 1
    # Zxx1[mask1] = 0
    # Zxx2[mask2] = 0
    #     for i in range(Zxx.shape[0]):

    #         if i % 15 < 9:
    #             Zxx1[i,:] = 0
    #         else:
    #             Zxx2[i,:] = 0
    _, sound1 = signal.istft(Zxx1, sample_rate, nperseg=nperseg, noverlap=noverlap)
    _, sound2 = signal.istft(Zxx2, sample_rate, nperseg=nperseg, noverlap=noverlap)

    return sound1, sound2, (mask, f, t, Zxx)


def dry_wet(sound, original, wet):
    return sound[:len(original)] * wet + original * (1 - wet)


# def dry_wet_stereo(sound1, sound2, mono, wet):
#     return dry_wet(sound1, mono, wet), dry_wet(sound2, mono, wet)

def multiply_masks_with_weights(masks, weights):
    masks = map(lambda mask : mask * 2 - 1, masks) # remap [0, 1] -> [-1, 1]
    total_weight = sum(weights)
    masks = [mask * weight / total_weight for mask, weight in zip(masks, weights)]
    mask = sum(masks)
    mask = (mask + 1) / 2 # remap [-1, 1] -> [0, 1]
    return mask

def dry_wet_mask(mask, wet):
    return (mask - 0.5) * wet + 0.5

def calc_real_mask_strength(mask):
    return 1 - min(np.min(mask), 1 - np.max(mask)) * 2

# noinspection PyTypeChecker
def audio_mono_stereo(mono, sound1, sound2, sample_rate):
    print("stereo:")
    display(Audio([sound1, sound2], rate=sample_rate, autoplay=True, normalize=True))
    print("mono:")
    display(Audio(mono, rate=sample_rate, autoplay=False, normalize=True))


# def test_method(method, song, song_rate, *args, **kwargs):
#     global sound1, sound2
#     sound1, sound2 = method(song, song_rate, *args, **kwargs)
#     audio_mono_stereo(song, sound1, sound2, song_rate)
#


#
# def mask_func1(bands_count=10, dry_wet_coeff=0.8):
#     # sound1, sound2 = m2s_freq_split(song, song_rate, split_into_bands_by_sound_volume(bands_count))
#     # sound1, sound2 = dry_wet_stereo(sound1, sound2, song, dry_wet_coeff)
#     # return sound1, sound2
#     def __func(Zxx):
#         mask = split_into_bands_by_sound_volume(bands_count)(Zxx)
#         return dry_wet_mask(mask, dry_wet_coeff)
#
#     return __func
#
#
# def mask_func2(smooth_coeff=30, is_dynamic=False, dynamic_time_period=20):
#     # sound1, sound2 = m2s_freq_split(song, song_rate, split_into_bands_by_parts(
#     #     is_dynamic=is_dynamic,
#     #     convolution_kernel=gen_sine_weights(smooth_coeff),
#     #     dynamic_time_period=dynamic_time_period,
#     # ))
#     return split_into_bands_by_parts(is_dynamic, gen_sine_weights(smooth_coeff), dynamic_time_period)
#
#



# mask = split_into_bands(Zxx, 10)
