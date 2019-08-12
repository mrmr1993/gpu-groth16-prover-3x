#include "cuda_prover_piecewise.hpp"

#include "libsnark/zk_proof_systems/ppzksnark/r1cs_gg_ppzksnark/r1cs_gg_ppzksnark.hpp"

extern "C" {

libsnark::r1cs_gg_ppzksnark_proof<libff::mnt4753_pp> *mnt4753_cuda_make_proof(
        size_t primary_input_size,
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
        params->d,
        params->m,
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

mnt4753_libsnark::groth16_params *mnt4753_groth16_params(
        const char *filename)
{
    FILE *params = fopen(filename, "r");
    size_t d = read_size_t(params);
    size_t m = read_size_t(params);
    rewind(params);
    mnt4753_libsnark::groth16_params *ret = mnt4753_libsnark::read_params(params, d, m);
    fclose(params);
    return ret;
}

mnt4753_libsnark::groth16_input *mnt4753_groth16_inputs(
        size_t d,
        size_t m,
        const char *filename)
{
    FILE *inputs = fopen(filename, "r");
    rewind(inputs);
    mnt4753_libsnark::groth16_input *ret = mnt4753_libsnark::read_input(inputs, d, m);
    fclose(inputs);
    return ret;
}

size_t mnt4753_params_d(mnt4753_libsnark::groth16_params *params)
{
    return params->d;
}
size_t mnt4753_params_m(mnt4753_libsnark::groth16_params *params)
{
    return params->m;
}

var *mnt4753_load_scalars(const size_t m, const char *filename)
{
    FILE *inputs = fopen(filename, "r");
    auto w_ = load_scalars(m + 1, inputs);
    fclose(inputs);
    return w_.release();
}

const void *mnt4753_get_input_witness(mnt4753_libsnark::groth16_input *inputs)
{
    return inputs->w.get();
}

libsnark::r1cs_gg_ppzksnark_proof<libff::mnt6753_pp> *mnt6753_cuda_make_proof(
        size_t primary_input_size,
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
        params->d,
        params->m,
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

mnt6753_libsnark::groth16_params *mnt6753_groth16_params(
        const char *filename)
{
    FILE *params = fopen(filename, "r");
    size_t d = read_size_t(params);
    size_t m = read_size_t(params);
    rewind(params);
    mnt6753_libsnark::groth16_params *ret = mnt6753_libsnark::read_params(params, d, m);
    fclose(params);
    return ret;
}

mnt6753_libsnark::groth16_input *mnt6753_groth16_inputs(
        size_t d,
        size_t m,
        const char *filename)
{
    FILE *inputs = fopen(filename, "r");
    rewind(inputs);
    mnt6753_libsnark::groth16_input *ret = mnt6753_libsnark::read_input(inputs, d, m);
    fclose(inputs);
    return ret;
}

size_t mnt6753_params_d(mnt6753_libsnark::groth16_params *params)
{
    return params->d;
}
size_t mnt6753_params_m(mnt6753_libsnark::groth16_params *params)
{
    return params->m;
}

var *mnt6753_load_scalars(const size_t m, const char *filename)
{
    FILE *inputs = fopen(filename, "r");
    auto w_ = load_scalars(m + 1, inputs);
    fclose(inputs);
    return w_.release();
}

}

const void *mnt6753_get_input_witness(mnt6753_libsnark::groth16_input *inputs)
{
    return inputs->w.get();
}
