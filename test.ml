let r = 32

let c = 5

let () =
  let open Groth16_gpu_prover.Mnt4753 in
  let params = Params.load "MNT4753-parameters" in
  let m = Params.m params in
  let d = Params.d params in
  let inputs = Inputs.load ~d ~m "MNT4753-input" in
  let c_exp = Unsigned.Size_t.(sub (shift_left one c) one) in
  let preprocessed_file =
    Groth16_gpu_prover.CFile.create "MNT4753_preprocessed" "r"
  in
  let c_exp_mul_m1 = Unsigned.Size_t.(mul c_exp (add m one)) in
  let b1_mults = load_points_affine c_exp_mul_m1 preprocessed_file in
  let b2_mults = load_extension_points_affine c_exp_mul_m1 preprocessed_file in
  let l_mults =
    load_points_affine
      Unsigned.Size_t.(mul c_exp (sub m one))
      preprocessed_file
  in
  let w = load_scalars Unsigned.Size_t.(add m one) "MNT4753-input" in
  Groth16_gpu_prover.CFile.destroy preprocessed_file ;
  let proof =
    Groth16_gpu_prover.Mnt4753.make_groth16_proof Unsigned.Size_t.one ~w
      ~b1_mults ~b2_mults ~l_mults params inputs
  in
  Format.(fprintf std_formatter) "Proof generated@." ;
  (*Snarky.Bin_prot_io.write (module Snarky.Libsnark.Mnt4753.Default.Proof) "MNT4753-output_ml" ~data:proof ;*)
  let keystring = Core_kernel.In_channel.read_all "verification-key.debug" in
  Format.(fprintf std_formatter) "Read key@." ;
  let key = Snarky.Libsnark.Mnt4753.Default.Verification_key.of_string keystring in
  Format.(fprintf std_formatter) "Got key@." ;
  let witness = Inputs.witness inputs in
  let public_inputs =
    let open Snarky.Libsnark.Mnt4753.Field.Vector in
    let v = create () in
    emplace_back v (get witness 0) ;
    v
  in
  Format.(fprintf std_formatter) "Got inputs@." ;
  assert (Snarky.Libsnark.Mnt4753.Default.Proof.verify proof key public_inputs) ;
  ignore proof
