#include <string>
#include <chrono>

#define NDEBUG 1

#include <prover_reference_libsnark.hpp>

void mnt4753_cuda_prove(
        mnt4753_libsnark::G1 **A_out,
        mnt4753_libsnark::G2 **B_out,
        mnt4753_libsnark::G1 **C_out,
        size_t primary_input_size,
        size_t d,
        size_t m,
        const var *w,
        // const var *A_mults,
        const var *B1_mults,
        const var *B2_mults,
        const var *L_mults,
        mnt4753_libsnark::groth16_params *params,
        mnt4753_libsnark::groth16_input *inputs);

void mnt6753_cuda_prove(
        mnt6753_libsnark::G1 **A_out,
        mnt6753_libsnark::G2 **B_out,
        mnt6753_libsnark::G1 **C_out,
        size_t primary_input_size,
        size_t d,
        size_t m,
        const var *w,
        // const var *A_mults,
        const var *B1_mults,
        const var *B2_mults,
        const var *L_mults,
        mnt6753_libsnark::groth16_params *params,
        mnt6753_libsnark::groth16_input *inputs);

libsnark::r1cs_se_ppzksnark_proof<T> *mnt4753_make_proof(
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
    mnt4753_libsnark::G1 **A_out, **C_out;
    mnt4753_libsnark::G2 **B_out;
    prove<R, C, B>(
        A_out,
        B_out,
        C_out,
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
    return new libsnark::r1cs_se_ppzksnark_proof<T>(A_out, B_out, C_out);
}

libsnark::r1cs_se_ppzksnark_proof<T> *mnt6753_make_proof(
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
    mnt6753_libsnark::G1 **A_out, **C_out;
    mnt6753_libsnark::G2 **B_out;
    prove<R, C, B>(
        A_out,
        B_out,
        C_out,
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
    return new libsnark::r1cs_se_ppzksnark_proof<T>(A_out, B_out, C_out);
}
