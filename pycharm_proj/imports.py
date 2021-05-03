import numpy as np
from IPython.display import Audio, display
import pywt
import scipy.fft as fft
import scipy.signal as signal
import matplotlib.pyplot as plt
import matplotlib.mlab as mlab
import matplotlib.patches as mpatches
import librosa
import scipy.ndimage.filters as ndfilters


import chart_studio.plotly as py
import plotly.graph_objects as go
import plotly.express as px
from ipywidgets import widgets
import dash_html_components as html
import dash_core_components as dcc
from dash.dependencies import Input, Output

from create_spectrogram import *
from audio_processing import *
from render_audio import *


guitar_sample, guitar_sample_rate = librosa.load("samples/guitar.wav")

(guitar_fl1, guitar_fl2), guitar_fl_sample_rate = librosa.load("samples/guitar_fl.wav", mono=False)

electro_sample, electro_sample_rate = librosa.load("samples/electro.wav")

jazz_sample, jazz_sample_rate = librosa.load("samples/jazz.wav")
jazz_sample /= np.max(np.abs(jazz_sample))

(guitar_wd1, guitar_wd2), sample_rate = librosa.load("samples/guitar_wider.wav", mono=False)
guitar_wd1 = guitar_wd1[:len(guitar_fl1)]
guitar_wd2 = guitar_wd2[:len(guitar_fl2)]

(wider_decomp1, wider_decomp2), sample_rate = librosa.load("samples/wider_decomp.wav", mono=False)

ghostbusters_sample, ghostbusters_sample_rate = librosa.load("samples/ghostbusters.wav")
# Audio(guitar_sample, rate=guitar_sample_rate, autoplay=True)
# Audio(electro_sample, rate=electro_sample_rate, autoplay=True)
# Audio(jazz_sample, rate=jazz_sample_rate, autoplay=True)


