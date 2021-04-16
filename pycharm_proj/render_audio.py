from imports import *


#
# def show_phase(sound1, sound2, sample_rate):
#     fig_tuple1 = create_phase_figure(sound1, sample_rate)
#     fig_tuple2 = create_phase_figure(sound2, sample_rate)
#     display(render_figs([fig_tuple1, fig_tuple2]))
#
# def show_magnitude(sound, sample_rate):
#     fig_tuple = create_magnitude_figure(sound, sample_rate)
#     display(render_figs([fig_tuple]))
#
#



# returns tuple (figure, Sxx, apply_params_func)
def create_magnitude_figure(sound, sample_rate):
    Sxx, drawing_params = create_spectrogram(sound, sample_rate, "magnitude")
    fig, Sxx = create_spectrogram_figure(Sxx, drawing_params, title="Magnitude")

    def apply_params_to_magnitude_figure(checklist_options, log_scale_coeff):
        z = Sxx.copy()
        if "need_filter_low_values" in checklist_options:
            z[z < 0.005] = 0
        if "need_norm_per_row_values" in checklist_options:
            max_per_row = np.max(np.abs(z), axis=-1)[:, None]
            z = np.divide(z, max_per_row, out=np.zeros_like(z), where=max_per_row != 0)
            if np.max(z) != 0:
                z /= np.max(z)
        if "need_log_scale_values" in checklist_options:
            z = np.log10(z * log_scale_coeff + 1)

        fig.data[0].z = z

        if "need_log_scale_frequency" in checklist_options:
            fig.update_yaxes(type="log")
        else:
            fig.update_yaxes(type="linear")

    return fig, Sxx, apply_params_to_magnitude_figure

# returns tuple (figure, Sxx, apply_params_func)
def create_phase_figure(sound, sample_rate):
    Sxx, drawing_params = create_spectrogram(sound, sample_rate, "angle")
    Sxx2, drawing_params = create_spectrogram(sound, sample_rate, "magnitude")

    fig, Sxx = create_spectrogram_figure(Sxx, drawing_params, title="Phase", colorscale="HSV")


    def apply_params_to_phase_figure(checklist_options, log_scale_coeff):
        z = Sxx.copy()
        for i in range(z.shape[0]):
            z[i] += np.sin(np.linspace(0, log_scale_coeff, z.shape[1]))
        z[Sxx2 < 0.01] = 0
        fig.data[0].z = z
        if "need_log_scale_frequency" in checklist_options:
            fig.update_yaxes(type="log")
        else:
            fig.update_yaxes(type="linear")

    return fig, Sxx, apply_params_to_phase_figure

# returns figure and new Sxx
def create_spectrogram_figure(Sxx, drawing_params, title, colorscale="Bluered"):
    t = drawing_params["t"]
    freqs = drawing_params["freqs"]
    # not need Sxx = np.flipud(Sxx)
    trace = [go.Heatmap(
        x=t,
        y=freqs,
        z=Sxx,
        colorscale=colorscale#'Bluered'  # 'Jet',
        )]
    # trace = [go.Image(
    #     z=[[(0, 1, 1)]],
    #     # x=t,
    #     # y=freqs,
    #     # color_continuous_scale=colorscale
    # )]
    layout = go.Layout(
        title=title,
        yaxis=dict(title='Frequency'),  # x-axis label
        xaxis=dict(title='Time'),   # y-axis label
        )
    return go.Figure(data=trace, layout=layout), Sxx



# data = [(fig, Sxx), ...]
# def render_figs(data):
#     figs = [i[0] for i in data]
#     need_norm_per_row_values = widgets.Checkbox(
#         description='norm values per row',
#         value=True
#     )
#     need_log_scale_values = widgets.Checkbox(
#         description='log scale values',
#         value=True,
#     )
#     log_scale_coeff = widgets.IntSlider(
#         description='log scale coeff',
#         value=100,
#         min=50,
#         max=1000,
#         continuous_update=False
#     )
#
#     need_log_scale_frequency = widgets.Checkbox(
#         description='log scale freqs',
#         value=False,
#     )
#
#     def response(change):
#         for (fig, Sxx) in data:
#             with fig.batch_update():
#                 z = Sxx
#                 if need_norm_per_row_values.value:
#                     max_per_row = np.max(np.abs(z), axis=-1)[:, None]
#                     z = np.divide(z, max_per_row, out=np.zeros_like(z), where=max_per_row != 0)
#                     z /= np.max(z)
#                 if need_log_scale_values.value:
#                     z = np.log10(z * log_scale_coeff.value + 1)
#
#                 fig.data[0].z = z
#
#                 if need_log_scale_frequency.value:
#                     fig.update_yaxes(type="log")
#                 else:
#                     fig.update_yaxes(type="linear")
#
#     need_norm_per_row_values.observe(response, names="value")
#     need_log_scale_values.observe(response, names="value")
#     need_log_scale_frequency.observe(response, names="value")
#     log_scale_coeff.observe(response, names="value")
#     response(None)
#
#     up_menu = widgets.VBox([need_norm_per_row_values,
#                             widgets.HBox([need_log_scale_values, log_scale_coeff]),
#                             need_log_scale_frequency])
#     return widgets.VBox([up_menu, widgets.HBox(figs)])

