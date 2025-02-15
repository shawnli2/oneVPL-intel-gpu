// Copyright (c) 2017-2020 Intel Corporation
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __UMC_AV1_MSFT_DDI_H
#define __UMC_AV1_MSFT_DDI_H

#pragma warning(disable: 4201)

#ifdef UMC_VA_DXVA

typedef struct _DXVA_PicEntry_AV1_MSFT {

    UINT width;
    UINT height;

    // Global motion parameters
    INT wmmat[6];
    union {
        struct {
            UCHAR wminvalid : 1;
            UCHAR wmtype : 2;
            UCHAR Reserved : 5;
        };
        UCHAR wGlobalMotionFlags;
    };

    UCHAR Index;
    USHORT Reserved16Bits;

} DXVA_PicEntry_AV1_MSFT, *LPDXVA_PicEntry_AV1;

typedef struct _DXVA_PicParams_AV1_MSFT {
    UINT width;
    UINT height;

    UINT max_width;
    UINT max_height;

    UCHAR CurrPicTextureIndex;
    UCHAR superres_denom;
    UCHAR BitDepth;
    UCHAR profile;

    // Tiles:
    struct {
        UCHAR cols;
        UCHAR rows;
        USHORT context_update_id;
        USHORT widths[64];
        USHORT heights[64];
    } tiles;

    // Coding Tools
    union {
        struct {
            UINT use_128x128_superblock : 1;
            UINT intra_edge_filter : 1;
            UINT interintra_compound : 1;
            UINT masked_compound : 1;
            UINT warped_motion : 1;
            UINT dual_filter : 1;
            UINT jnt_comp : 1;
            UINT screen_content_tools : 1;
            UINT integer_mv : 1;
            UINT cdef : 1;
            UINT restoration : 1;
            UINT film_grain : 1;
            UINT intrabc : 1;
            UINT high_precision_mv : 1;
            UINT switchable_motion_mode : 1;
            UINT filter_intra : 1;
            UINT disable_frame_end_update_cdf : 1;
            UINT disable_cdf_update : 1;
            UINT reference_mode : 1;
            UINT skip_mode : 1;
            UINT reduced_tx_set : 1;
            UINT superres : 1;
            UINT tx_mode : 2;
            UINT use_ref_frame_mvs : 1;
            UINT enable_ref_frame_mvs : 1;
            UINT reference_frame_update : 1;
            UINT Reserved : 5;
        };
        UINT dwCodingParamToolFlags;
    } coding;

    // Format & Picture Info flags
    union {
        struct {
            UCHAR frame_type : 2;
            UCHAR show_frame : 1;
            UCHAR showable_frame : 1;
            UCHAR subsampling_x : 1;
            UCHAR subsampling_y : 1;
            UCHAR mono_chrome : 1;
            UCHAR Reserved : 1;
        };
        UCHAR wFormatAndPictureInfoFlags;
    } format;

    // References
    UCHAR primary_ref_frame;
    UCHAR order_hint;
    UCHAR order_hint_bits;

    DXVA_PicEntry_AV1_MSFT frame_refs[7];
    UCHAR ref_frame_map_texture_index[8];

    // Loop filter parameters
    struct {
        UCHAR filter_level[2];
        UCHAR filter_level_u;
        UCHAR filter_level_v;

        UCHAR sharpness_level;
        union {
            struct {
                UCHAR mode_ref_delta_enabled : 1;
                UCHAR mode_ref_delta_update : 1;
                UCHAR delta_lf_multi : 1;
                UCHAR delta_lf_present : 1;
                UCHAR Reserved : 4;
            };
            UCHAR wControlFlags;
        };
        CHAR ref_deltas[8];
        CHAR mode_deltas[2];
        UCHAR delta_lf_res;
        UCHAR frame_restoration_type[3];
        USHORT log2_restoration_unit_size[3];
        USHORT Reserved16Bits;
    } loop_filter;

    // Quantization
    struct {
        union {
            struct {
                UCHAR delta_q_present : 1;
                UCHAR delta_q_res : 2;
                UCHAR Reserved : 5;
            };
            UCHAR wControlFlags;
        };

        UCHAR base_qindex;
        CHAR y_dc_delta_q;
        CHAR u_dc_delta_q;
        CHAR v_dc_delta_q;
        CHAR u_ac_delta_q;
        CHAR v_ac_delta_q;
        // using_qmatrix:
        UCHAR qm_y;
        UCHAR qm_u;
        UCHAR qm_v;
        USHORT Reserved16Bits;
    } quantization;

    // Cdef parameters
    struct {
        union {
            struct {
                UCHAR damping : 2;
                UCHAR bits : 2;
                UCHAR Reserved : 4;
            };
            UCHAR wControlFlags;
        };

        union {
            struct {
                UCHAR primary : 6;
                UCHAR secondary : 2;
            };
            UCHAR combined;
        } y_strengths[8];

        union {
            struct {
                UCHAR primary : 6;
                UCHAR secondary : 2;
            };
            UCHAR combined;
        } uv_strengths[8];

    } cdef;

    UCHAR interp_filter;

    // Segmentation
    struct {
        union {
            struct {
                UCHAR enabled : 1;
                UCHAR update_map : 1;
                UCHAR update_data : 1;
                UCHAR temporal_update : 1;
                UCHAR Reserved : 4;
            };
            UCHAR wControlFlags;
        };
        UCHAR  Reserved24Bits[3];

        union
        {
            struct
            {
                UCHAR alt_q : 1;
                UCHAR alt_lf_y_v : 1;
                UCHAR alt_lf_y_h : 1;
                UCHAR alt_lf_u : 1;
                UCHAR alt_lf_v : 1;
                UCHAR ref_frame : 1;
                UCHAR skip : 1;
                UCHAR globalmv : 1;
            };
            UCHAR mask;
        } feature_mask[8];
        SHORT feature_data[8][8];

    } segmentation;

    struct {
        union {
            struct {
                USHORT apply_grain : 1;
                USHORT scaling_shift_minus8 : 2;
                USHORT chroma_scaling_from_luma : 1;
                USHORT ar_coeff_lag : 2;
                USHORT ar_coeff_shift_minus6 : 2;
                USHORT grain_scale_shift : 2;
                USHORT overlap_flag : 1;
                USHORT clip_to_restricted_range : 1;
                USHORT matrix_coeff_is_identity : 1;
                USHORT Reserved : 3;
            };
            USHORT wControlFlags;
        };

        USHORT grain_seed;
        UCHAR scaling_points_y[14][2];
        UCHAR num_y_points;
        UCHAR scaling_points_cb[10][2];
        UCHAR num_cb_points;
        UCHAR scaling_points_cr[10][2];
        UCHAR num_cr_points;
        UCHAR ar_coeffs_y[24];
        UCHAR ar_coeffs_cb[25];
        UCHAR ar_coeffs_cr[25];
        UCHAR cb_mult;
        UCHAR cb_luma_mult;
        UCHAR cr_mult;
        UCHAR cr_luma_mult;
        UCHAR Reserved8Bits;
        SHORT cb_offset;
        SHORT cr_offset;
    } film_grain;

    UINT   Reserved32Bits;
    UINT   StatusReportFeedbackNumber;
} DXVA_PicParams_AV1_MSFT, *LPDXVA_PicParams_AV1;

typedef struct _DXVA_Tile_AV1 {
    UINT   dataOffset;
    UINT   dataSize;
    USHORT row;
    USHORT column;
    USHORT Reserved16Bits;
    UCHAR anchor_frame;
    UCHAR Reserved8Bits;
} DXVA_Tile_AV1, *LPDXVA_Tile_AV1;

typedef struct _DXVA_Status_AV1 {
    UINT  StatusReportFeedbackNumber;
    DXVA_PicEntry_AV1_MSFT CurrPic;
    UCHAR  bBufType;
    UCHAR  bStatus;
    UCHAR  bReserved8Bits;
    USHORT wNumMbsAffected;
} DXVA_Status_AV1, *LPDXVA_Status_AV1;
#endif
#endif