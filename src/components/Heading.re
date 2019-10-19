open DesignSystem;

type level = [ | `h1 | `h2 | `h3 | `h4];

module Classes = {
  open Css;

  let heading = level => {
    let (font, mb) =
      switch (level) {
      | `h1 => (Styles.font(`xxl), Styles.space(`md))
      | `h2 => (Styles.font(`xl), Styles.space(`md))
      | `h3 => (Styles.font(`lg), Styles.space(`sm))
      | `h4 => (Styles.font(`md), Styles.space(`xs))
      };

    style([marginBottom(mb), ...font]);
  };
};

[@react.component]
let make = (~level=`h1, ~className as cn="", ~children, ()) => {
  let className = Css.merge([Classes.heading(level), cn]);

  switch (level) {
  | `h1 => <h1 className> children </h1>
  | `h2 => <h2 className> children </h2>
  | `h3 => <h3 className> children </h3>
  | `h4 => <h4 className> children </h4>
  };
};
