#include "cuda_prover_piecewise.hpp"

#include "libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp"

extern "C" {

libsnark::r1cs_gg_ppzksnark_proof<libff::mnt4753_pp> *mnt4753_cuda_make_proof(
        size_t primary_input_size,
        size_t d,
        size_t m,
        const var *w,
        // const var *A_mults,
        const var *B1_mults,
        const var *B2_mults,
        const var *L_mults,
        mnt4753_libsnark::groth16_params *params,
        mnt4753_libsnark::groth16_input *inputs)
{
    mnt4753_libsnark::G1 *A_out = NULL, *C_out = NULL;
    mnt4753_libsnark::G2 *B_out = NULL;
    mnt4753_cuda_prove(
        &A_out,
        &B_out,
        &C_out,
        primary_input_size,
        d,
        m,
        w,
        // A_mults,
        B1_mults,
        B2_mults,
        L_mults,
        params,
        inputs);

    libsnark::r1cs_gg_ppzksnark_proof<libff::mnt4753_pp> *proof =
      new libsnark::r1cs_gg_ppzksnark_proof<libff::mnt4753_pp>();

    proof->g_A = A_out->data;
    proof->g_B = B_out->data;
    proof->g_C = C_out->data;

    return proof;
}

libsnark::r1cs_gg_ppzksnark_proof<libff::mnt6753_pp> *mnt6753_cuda_make_proof(
        size_t primary_input_size,
        size_t d,
        size_t m,
        const var *w,
        // const var *A_mults,
        const var *B1_mults,
        const var *B2_mults,
        const var *L_mults,
        mnt6753_libsnark::groth16_params *params,
        mnt6753_libsnark::groth16_input *inputs)
{
    mnt6753_libsnark::G1 *A_out = NULL, *C_out = NULL;
    mnt6753_libsnark::G2 *B_out = NULL;
    mnt6753_cuda_prove(
        &A_out,
        &B_out,
        &C_out,
        primary_input_size,
        d,
        m,
        w,
        // A_mults,
        B1_mults,
        B2_mults,
        L_mults,
        params,
        inputs);

    libsnark::r1cs_gg_ppzksnark_proof<libff::mnt6753_pp> *proof =
      new libsnark::r1cs_gg_ppzksnark_proof<libff::mnt6753_pp>();

    proof->g_A = A_out->data;
    proof->g_B = B_out->data;
    proof->g_C = C_out->data;

    return proof;
}

}
