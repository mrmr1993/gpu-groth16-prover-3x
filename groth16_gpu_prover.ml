open Snarky
open Ctypes
open Foreign

module Mnt4753 = struct
  (* Linking stub *)
  external _stub : unit -> unit = "mnt4753_cuda_make_proof"

  let _stub = ()

  let make_groth16_proof =
    let stub =
      foreign "mnt4753_cuda_make_proof"
        ( int @-> Libsnark.Mnt4753.Field.Vector.typ
        @-> Libsnark.Mnt4753.Field.Vector.typ
        @-> Libsnark.Mnt4753.G1.Vector.typ @-> Libsnark.Mnt4753.G2.Vector.typ
        @-> Libsnark.Mnt4753.G1.Vector.typ
        @-> Libsnark.Mnt4753.Default.Proving_key.typ
        @-> returning Libsnark.Mnt4753.Default.Proof.typ )
    in
    fun ~public_input ~auxiliary_input ~b1_mults ~b2_mults ~l_mults c pk ->
      stub c public_input auxiliary_input b1_mults b2_mults l_mults pk
end

module Mnt6753 = struct
  let make_groth16_proof =
    let stub =
      foreign "mnt6753_cuda_make_proof"
        ( int @-> Libsnark.Mnt6753.Field.Vector.typ
        @-> Libsnark.Mnt6753.Field.Vector.typ
        @-> Libsnark.Mnt6753.G1.Vector.typ @-> Libsnark.Mnt6753.G2.Vector.typ
        @-> Libsnark.Mnt6753.G1.Vector.typ
        @-> Libsnark.Mnt6753.Default.Proving_key.typ
        @-> returning Libsnark.Mnt6753.Default.Proof.typ )
    in
    fun ~public_input ~auxiliary_input ~b1_mults ~b2_mults ~l_mults c pk ->
      stub c public_input auxiliary_input b1_mults b2_mults l_mults pk
end
