// Copyright (c) Meta Platforms, Inc. and affiliates.

// This software may be used and distributed according to the terms of the
// GNU General Public License version 2.


/// Atropos is a multi-domain BPF / userspace hybrid scheduler where the BPF
/// part does simple round robin in each domain and the userspace part
/// calculates the load factor of each domain and tells the BPF part how to load
/// balance the domains.

/// This scheduler demonstrates dividing scheduling logic between BPF and
/// userspace and using rust to build the userspace part. An earlier variant of
/// this scheduler was used to balance across six domains, each representing a
/// chiplet in a six-chiplet AMD processor, and could match the performance of
/// production setup using CFS.
