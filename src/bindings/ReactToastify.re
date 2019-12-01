type transition;
module ToastContainer = {
  [@bs.module "react-toastify"] [@react.component]
  external make:
    (
      ~transition: transition=?,
      ~hideProgressBar: bool=?,
      ~closeButton: bool, // can also be React.element=?,
      ~toastClassName: string=?,
      ~className: string=?,
      ~autoClose: int=?,
      ~position: string=?
    ) =>
    React.element =
    "ToastContainer";
};

[@bs.module "react-toastify"] external toast: string => unit = "toast";

[@bs.module "react-toastify"] external slide: transition = "Slide";
[@bs.module "react-toastify"] external flip: transition = "Flip";
