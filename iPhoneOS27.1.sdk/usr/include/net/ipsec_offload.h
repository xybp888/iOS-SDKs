/*
 * Copyright (c) 2026 Apple Inc. All rights reserved.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_START@
 *
 * This file contains Original Code and/or Modifications of Original Code
 * as defined in and that are subject to the Apple Public Source License
 * Version 2.0 (the 'License'). You may not use this file except in
 * compliance with the License. The rights granted to you under the License
 * may not be used to create, or enable the creation or redistribution of,
 * unlawful or unlicensed copies of an Apple operating system, or to
 * circumvent, violate, or enable the circumvention or violation of, any
 * terms of an Apple operating system software license agreement.
 *
 * Please obtain a copy of the License at
 * http://www.opensource.apple.com/apsl/ and read it before using this file.
 *
 * The Original Code and all software distributed under the License are
 * distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESS OR IMPLIED, AND APPLE HEREBY DISCLAIMS ALL SUCH WARRANTIES,
 * INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, QUIET ENJOYMENT OR NON-INFRINGEMENT.
 * Please see the License for the specific language governing rights and
 * limitations under the License.
 *
 * @APPLE_OSREFERENCE_LICENSE_HEADER_END@
 */
#ifndef _IPSEC_OFFLOAD_H_
#define _IPSEC_OFFLOAD_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

/* Increase if ABI-breaking changes are added */
#define IPSEC_OFFLOAD_KPI_VERSION       2

/* Protocol / mode */
typedef enum ipsec_offload_proto {
	IPSEC_OFFLOAD_PROTO_ESP = 50,
	IPSEC_OFFLOAD_PROTO_AH  = 51
} ipsec_offload_proto_t;

typedef enum ipsec_offload_mode {
	IPSEC_OFFLOAD_MODE_TRANSPORT = 0,
	IPSEC_OFFLOAD_MODE_TUNNEL    = 1
} ipsec_offload_mode_t;

/* Direction type for SA and policy */
typedef enum ipsec_offload_dir {
	IPSEC_OFFLOAD_DIR_IN  = 1,      /* inbound/receive */
	IPSEC_OFFLOAD_DIR_OUT = 2,      /* outbound/transmit */
	IPSEC_OFFLOAD_DIR_FWD = 3       /* forward (optional) */
} ipsec_offload_dir_t;

/*
 * Policy action.  The kernel asks the driver to install one rule per
 * policy; this tells the driver whether to encrypt/decrypt (ALLOW) or
 * to drop matching packets in hardware (DISCARD).  The two map directly
 * to PF_KEY's IPSEC_POLICY_IPSEC and IPSEC_POLICY_DISCARD respectively.
 * BYPASS/NONE policies don't need driver-side state and are not
 * offloaded.
 */
typedef enum ipsec_offload_action {
	IPSEC_OFFLOAD_ACTION_ALLOW   = 1,  /* apply IPsec (encrypt/decrypt) */
	IPSEC_OFFLOAD_ACTION_DISCARD = 2,  /* drop matching packets in HW */
} ipsec_offload_action_t;

/* Algorithm definitions taken from <net/pfkeyv2.h> */
/* RFC2367 numbers - meets RFC2407 */
#define IPSEC_OFFLOAD_AALG_NONE          0
#define IPSEC_OFFLOAD_AALG_MD5HMAC       1       /*2*/
#define IPSEC_OFFLOAD_AALG_SHA1HMAC      2       /*3*/
#define IPSEC_OFFLOAD_AALG_MAX           8
/* private allocations - based on RFC2407/IANA assignment */
#define IPSEC_OFFLOAD_X_AALG_SHA2_256    6       /*5*/
#define IPSEC_OFFLOAD_X_AALG_SHA2_384    7       /*6*/
#define IPSEC_OFFLOAD_X_AALG_SHA2_512    8       /*7*/
/* private allocations should use 249-255 (RFC2407) */
#define IPSEC_OFFLOAD_X_AALG_MD5         3       /*249*/ /* Keyed MD5, not implemented */
#define IPSEC_OFFLOAD_X_AALG_SHA         4       /*250*/ /* Keyed SHA, not implemented */
#define IPSEC_OFFLOAD_X_AALG_NULL        5       /*251*/ /* null authentication */

/* RFC2367 numbers - meets RFC2407 */
#define IPSEC_OFFLOAD_EALG_NONE          0
#define IPSEC_OFFLOAD_EALG_DESCBC        1       /*2*/
#define IPSEC_OFFLOAD_EALG_3DESCBC       2       /*3*/
#define IPSEC_OFFLOAD_EALG_NULL          3       /*11*/
#define IPSEC_OFFLOAD_EALG_MAX           12
/* private allocations - based on RFC2407/IANA assignment */
#define IPSEC_OFFLOAD_X_EALG_CAST128CBC  5       /*6*/
#define IPSEC_OFFLOAD_X_EALG_BLOWFISHCBC 4       /*7*/
#define IPSEC_OFFLOAD_X_EALG_RIJNDAELCBC 12
#define IPSEC_OFFLOAD_X_EALG_AESCBC      12
#define IPSEC_OFFLOAD_X_EALG_AES         12
#define IPSEC_OFFLOAD_X_EALG_AES_GCM     13
#define IPSEC_OFFLOAD_X_EALG_CHACHA20POLY1305 14
#define IPSEC_OFFLOAD_X_EALG_AES_GMAC    15
/* private allocations should use 249-255 (RFC2407) */

/*
 * Keying material
 *
 * Keys are stored inline in fixed-size arrays.  key_enc_key_len and
 * key_auth_key_len indicate the valid bytes; unused trailing bytes
 * are zeroed.  Maximum supported key length is IPSEC_OFFLOAD_MAX_KEY_LEN.
 *
 * AEAD (e.g. AES-GCM, ChaCha20-Poly1305, AES-GMAC):
 *   key_aead_alg != 0; key_enc_alg = key_auth_alg = 0.
 *   key_enc_key/key_enc_key_len = AEAD key (16 or 32 bytes, excludes salt).
 *   key_auth_key/key_auth_key_len = unused (0).
 *   key_salt  = per-SA AEAD salt (4 bytes, extracted from raw key material).
 *   key_icv_len = authentication tag length in bytes (e.g. 16 for AES-GCM-16);
 *                 derived from algorithm, not independently configurable.
 *
 * Non-AEAD:
 *   key_aead_alg = 0.
 *   key_enc_alg  = IPSEC_OFFLOAD_EALG_* or IPSEC_OFFLOAD_X_EALG_* (0 if AH-only).
 *   key_auth_alg = IPSEC_OFFLOAD_AALG_* or IPSEC_OFFLOAD_X_AALG_* (0 if none).
 *   key_enc_key/key_auth_key populated as applicable; key_salt typically 0.
 *   key_icv_len = MAC/ICV truncation length in bytes (0 = algorithm default);
 *                 derived from algorithm, not independently configurable.
 */
#define IPSEC_OFFLOAD_MAX_KEY_LEN       64

typedef struct ipsec_offload_keymat {
	uint16_t        key_aead_alg;
	uint16_t        key_enc_alg;
	uint16_t        key_auth_alg;
	uint8_t         key_enc_key[IPSEC_OFFLOAD_MAX_KEY_LEN];
	uint16_t        key_enc_key_len;
	uint8_t         key_auth_key[IPSEC_OFFLOAD_MAX_KEY_LEN];
	uint16_t        key_auth_key_len;
	uint8_t         __reserved[2];   /* explicit padding so key_salt is
	                                  * 4-byte aligned in the wire layout */
	uint32_t        key_salt;
	uint16_t        key_icv_len;
} ipsec_offload_keymat_t;

/* IP version */
typedef enum ipsec_offload_ip_version {
	IPSEC_OFFLOAD_IPV4 = 4,
	IPSEC_OFFLOAD_IPV6 = 6
} ipsec_offload_ip_version_t;

/*
 * L4 protocol values for ipsec_offload_selector.sel_transport
 * 0 means "wildcard / no L4 match".
 */
typedef enum ipsec_offload_transport {
	IPSEC_OFFLOAD_L4_ANY = 0,   /* no L4 match */
	IPSEC_OFFLOAD_L4_TCP = 6,   /* TCP */
	IPSEC_OFFLOAD_L4_UDP = 17,  /* UDP */
} ipsec_offload_transport_t;

/* Selector for packet offload classification (inner flow) */
typedef struct ipsec_offload_selector {
	ipsec_offload_ip_version_t sel_ip_version; /* IP version */
	uint8_t                    sel_src[16];    /* source address, network order */
	uint8_t                    sel_dst[16];    /* destination address, network order */
	uint8_t                    sel_src_prefix; /* 32/128 for exact */
	uint8_t                    sel_dst_prefix; /* 32/128 for exact */
	ipsec_offload_transport_t  sel_transport;  /* transport proto */
	uint16_t                   sel_src_port;   /* source port, network order */
	uint16_t                   sel_dst_port;   /* destination port, network order */
} ipsec_offload_selector_t;

/* Optional outer tunnel endpoints (used if mode == TUNNEL) */
typedef struct ipsec_offload_tunnel {
	ipsec_offload_ip_version_t tun_ip_version; /* IP version */
	uint8_t                    tun_src[16];    /* outer source IP, network order */
	uint8_t                    tun_dst[16];    /* outer destination IP, network order */
	uint8_t                    tun_hop_limit;  /* 0 = stack default */
} ipsec_offload_tunnel_t;

/* SA flags (bitfield) */
typedef enum ipsec_offload_sa_flags {
	IPSEC_OFFLOAD_SA_F_ESN = 1u << 0           /* Extended Sequence Numbers */
} ipsec_offload_sa_flags_t;

/* SA programming (used by crypto + packet offload) */
typedef struct ipsec_offload_sa {
	uint32_t                   sa_flags;       /* ipsec_offload_sa_flags_t */
	uint32_t                   sa_spi;         /* SPI (network order) */
	ipsec_offload_proto_t      sa_proto;       /* ESP / AH */
	ipsec_offload_mode_t       sa_mode;        /* Transport / Tunnel */
	ipsec_offload_dir_t        sa_dir;         /* IN / OUT / FWD */
	ipsec_offload_selector_t   sa_selector;    /* SA src/dst addresses, plus
	                                            * optional transport proto +
	                                            * src/dst ports.  Prefix
	                                            * lengths are 32 (IPv4) or
	                                            * 128 (IPv6) — SAs match by
	                                            * exact host addresses.
	                                            * Transport / ports default
	                                            * to ANY / 0 if userspace did
	                                            * not specify them. */
	ipsec_offload_keymat_t     sa_keys;        /* Keying material */
	uint32_t                   sa_replay_win;  /* anti-replay window size in bytes
	                                            * (e.g. 4/8/16/32 for 32/64/128/256-bit
	                                            * windows); 0 = disabled.
	                                            * Driver should reject unsupported sizes. */
	uint32_t                   sa_reqid;       /* Optional binding hint, 0 = unused */
	ipsec_offload_tunnel_t     sa_tunnel;      /* valid if mode == TUNNEL */
} ipsec_offload_sa_t;

/* Policy classifier (packet offload) */
typedef struct ipsec_offload_policy {
	ipsec_offload_dir_t        pol_dir;        /* IN / OUT / FWD */
	ipsec_offload_action_t     pol_action;     /* ALLOW = apply IPsec via the
	                                            * bound SA; DISCARD = HW drops
	                                            * matching packets. */
	ipsec_offload_selector_t   pol_sel;        /* flow match */

	/* Optional binding choices (driver may use either if provided): */
	uint32_t                   pol_reqid;      /* binding hint; 0 = unused */
	uint64_t                   pol_sa_handle;  /* direct SA cookie; 0 = resolve via reqid/SPI/etc. */
} ipsec_offload_policy_t;


#ifdef __cplusplus
}
#endif
#endif /* _IPSEC_OFFLOAD_H_ */
