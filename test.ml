let r = 32

let c = 5

let () =
  let open Groth16_gpu_prover.Mnt4753 in
  let params = Params.load "MNT4753-parameters" in
  let m = Params.m params in
  let d = Params.d params in
  let inputs = Inputs.load ~d ~m "MNT4753-input" in
  let preprocessed_file =
    Groth16_gpu_prover.CFile.create "MNT4753_preprocessed" "r"
  in
  let pkstring = Core_kernel.In_channel.read_all "proving-key.debug" in
  let proving_key = Snarky.Libsnark.Mnt4753.Default.Proving_key.of_string pkstring in
  let b1_mults_vec = Preprocess.b1 c proving_key in
  let b1_mults = Preprocess.reduce_g1_vector b1_mults_vec in
  let b2_mults_vec = Preprocess.b2 c proving_key in
  let b2_mults = Preprocess.reduce_g2_vector b2_mults_vec in
  let l_mults_vec = Preprocess.l c proving_key in
  let l_mults = Preprocess.reduce_g1_vector l_mults_vec in
  let w = load_scalars Unsigned.Size_t.(add m one) "MNT4753-input" in
  Groth16_gpu_prover.CFile.destroy preprocessed_file ;
  let witness = Inputs.witness inputs in
  let public_input =
    let open Snarky.Libsnark.Mnt4753.Field.Vector in
    let v = create () in
    emplace_back v (get witness 1) ;
    v
  in
  let auxiliary_input =
    let open Snarky.Libsnark.Mnt4753.Field.Vector in
    let v = create () in
    for i = 2 to length witness do
      emplace_back v (get witness i) ;
    done ;
    v
  in
  let proof =
    Groth16_gpu_prover.Mnt4753.make_groth16_proof ~w
      ~b1_mults ~b2_mults ~l_mults ~public_input ~auxiliary_input proving_key
  in
  let keystring = Core_kernel.In_channel.read_all "verification-key.debug" in
  let key = Snarky.Libsnark.Mnt4753.Default.Verification_key.of_string keystring in
  assert (Snarky.Libsnark.Mnt4753.Default.Proof.verify proof key public_input) ;
  ignore proof
