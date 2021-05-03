from imports import *
from audio_processing import *

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

def create_magnitude_figure2(sound1, sound2, sample_rate):
    Sxx1, drawing_params = create_spectrogram(sound1, sample_rate, "magnitude")
    Sxx2, drawing_params = create_spectrogram(sound2, sample_rate, "magnitude")
    fig, Sxx = create_spectrogram_figure(Sxx1 - Sxx2, drawing_params, title="Magnitude")

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





def create_dashed_method_with_mask():
    def create_layout(id: str):
        return [
            html.Div([
                html.B("Smooth"),
                dcc.Slider(
                    id="smooth_coeff" + id,
                    min=2,
                    max=100,
                    step=1,
                    value=30
                )
            ], style={'width': '300px', 'display': 'inline-block'}),
            html.Br(),
            dcc.RadioItems(
                id="smooth_type" + id,
                options=[
                    {'label': 'Sin', 'value': 'sin'},
                    {'label': 'Gaussian', 'value': 'gaussian'},
                ],
                value='gaussian',
                labelStyle={'display': 'inline-block'}
            ),

            html.Br(),

            html.Div([
                html.B("Effect strength (up to 500%)"),
                dcc.Slider(
                    id="weight_effect_strength" + id,
                    min=0,
                    max=500,
                    step=1,
                    value=100
                )
            ], style={'width': '1000px', 'display': 'inline-block'}),
            html.Br(),

            dcc.Checklist(
                id="maximum_strength" + id,
                options=[
                    {'label': 'Maximum strength', 'value': 'maximum_strength'},
                ],
                value=['maximum_strength']
            ),

            html.Div([
                html.B("Weight splitter"),
                dcc.Slider(
                    id="weight_split_by_parts" + id,
                    min=0,
                    max=100,
                    step=1,
                    value=30
                )
            ], style={'width': '300px', 'display': 'inline-block'}),

            html.Br(),
            dcc.RadioItems(
                id="split_type" + id,
                options=[
                    {'label': 'Simple spilt', 'value': 'by_parts'},
                    {'label': 'Split by volume', 'value': 'by_volume'},
                ],
                value='by_volume',
                labelStyle={'display': 'inline-block'}
            ),
            html.Br(),

            dcc.Checklist(
                id="dynamic" + id,
                options=[
                    {'label': 'dynamic', 'value': 'dynamic'},
                ],
                value=['dynamic']
            ),

            html.Div([
                "Dynamic time period",
                dcc.Slider(
                    id="dynamic_time_period" + id,
                    min=2,
                    max=100,
                    step=1,
                    value=30
                )
            ], style={'width': '300px', 'display': 'inline-block'}),
            html.Br(),

            html.Div([
                "Split by volume number of parts",
                dcc.Slider(
                    id="split_by_volume_numbands" + id,
                    min=0,
                    max=35,
                    step=1,
                    value=30
                )
            ], style={'width': '300px', 'display': 'inline-block'}),
            html.Br(),


            html.Div([
                html.B("Weight horizontal random"),
                dcc.Slider(
                    id="weight_horizontal_random" + id,
                    min=0,
                    max=100,
                    step=1,
                    value=30
                )
            ], style={'width': '300px', 'display': 'inline-block'}),

            html.Div([
                "Horizontal stretch",
                dcc.Slider(
                    id="horizontal_random_stretch" + id,
                    min=0,
                    max=35,
                    step=1,
                    value=30
                )
            ], style={'width': '300px', 'display': 'inline-block'}),
        ]

    def create_callback_inputs(id: str):
        return [Input('smooth_coeff' + id, "value"),
                Input('smooth_type' + id, "value"),
                Input("weight_effect_strength" + id, "value"),
                Input("weight_split_by_parts" + id, "value"),
                Input("split_type" + id, "value"),
                Input("dynamic" + id, "value"),
                Input("dynamic_time_period" + id, "value"),
                Input("split_by_volume_numbands" + id, "value"),
                Input("weight_horizontal_random" + id, "value"),
                Input("horizontal_random_stretch" + id, "value"),
                ]

    def method(sound, sample_rate, smooth_coeff, smooth_type, weight_effect_strength,
               weight_split_by_parts, split_type,
               dynamic_options, dynamic_time_period, split_by_volume_numbands, weight_horizontal_random,
               horizontal_random_stretch):
        def mask_func(Zxx):
            if split_type == "by_parts":
                split_by_parts_mask = split_into_bands_by_parts()(Zxx)
            else:
                split_by_parts_mask = split_into_bands_by_volume(numbands=split_by_volume_numbands)(Zxx)

            if "dynamic" in dynamic_options:
                split_by_parts_mask = apply_horizontal_split(split_by_parts_mask, dynamic_time_period=dynamic_time_period)

            split_by_random_horizontal_mask = split_into_bands_by_random_horizontal(horizontal_random_stretch)(Zxx)

            mask = multiply_masks_with_weights([split_by_parts_mask, split_by_random_horizontal_mask],
                                               [weight_split_by_parts, weight_horizontal_random])

            mask = apply_convolution_to_mask(mask, type=smooth_type, strength=smooth_coeff)


            if np.min(mask) + 0.01 < 0 or np.max(mask) - 0.01 > 1:
                raise Exception("Invalid mask " + str(mask))

            real_strength = calc_real_mask_strength(mask)
            mask = dry_wet_mask(mask, weight_effect_strength / 100 / real_strength)
            mask[mask > 1] = 1
            mask[mask < 0] = 0

            return mask

        sound1, sound2, (mask, f, t, Zxx) = m2s_with_mask(sound, sample_rate, mask_func)



        mmask = mask.copy()
        mmask[0, 0] = 0
        mmask[0, 1] = 1
        layout_addition = [
            "min: " + str(np.min(mask)) + " max: " + str(np.max(mask)) + " mean: " + str(np.mean(mask)) +
            "mean diff: " + str(np.mean(np.abs(mask - 0.5))),
            dcc.Graph(figure= create_spectrogram_figure(mmask, {"t": t, "freqs": f}, "mask")[0])
        ]
        return sound1 * 2, sound2 * 2, layout_addition


    return (method, create_layout, create_callback_inputs)


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

