open Snarky
open Ctypes
open Foreign

module CFile = struct
  module T : sig
    type t

    val typ : t typ
  end = struct
    type t = unit ptr

    let typ = ptr void
  end

  include T

  let create = foreign "fopen" (string @-> string @-> returning typ)

  let destroy = foreign "fclose" (typ @-> returning void)
end

module Mnt4753 = struct
  (* Linking stub *)
  external _stub : unit -> unit = "mnt4753_cuda_make_proof"

  let _stub = ()

  let load_scalars =
    foreign "mnt4753_load_scalars" (size_t @-> string @-> returning (ptr void))

  let load_points_affine =
    foreign "mnt4753_cuda_load_points_affine"
      (size_t @-> CFile.typ @-> returning (ptr void))

  let load_extension_points_affine =
    foreign "mnt4753_cuda_load_extension_points_affine"
      (size_t @-> CFile.typ @-> returning (ptr void))

  module Params = struct
    module T : sig
      type t

      val typ : t typ
    end = struct
      type t = unit ptr

      let typ = ptr void
    end

    include T

    let load = foreign "mnt4753_groth16_params" (string @-> returning typ)

    let d = foreign "mnt4753_params_d" (typ @-> returning size_t)

    let m = foreign "mnt4753_params_m" (typ @-> returning size_t)
  end

  module Inputs = struct
    module T : sig
      type t

      val typ : t typ
    end = struct
      type t = unit ptr

      let typ = ptr void
    end

    include T

    let load =
      let stub =
        foreign "mnt4753_groth16_inputs"
          (size_t @-> size_t @-> string @-> returning typ)
      in
      fun ~d ~m filename -> stub d m filename

    let witness =
      foreign "mnt4753_get_input_witness"
        (typ @-> returning Libsnark.Mnt4753.Field.Vector.typ )
  end

  let make_groth16_proof =
    let stub =
      foreign "mnt4753_cuda_make_proof"
        ( size_t @-> ptr void @-> ptr void @-> ptr void
        @-> ptr void @-> Params.typ @-> Inputs.typ
        @-> returning Libsnark.Mnt4753.Default.Proof.typ )
    in
    fun inputs_len ~w ~b1_mults ~b2_mults ~l_mults params inputs ->
      stub inputs_len w b1_mults b2_mults l_mults params inputs
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
