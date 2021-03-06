open DesignSystem;

module Classes = {
  open Css;

  let root =
    style([
      display(`flex),
      flexDirection(column),
      position(`relative),
      marginBottom(`sm |> Styles.space),
      width(pct(100.0)),
    ]);

  let input = (~error) =>
    style([
      width(pct(100.0)),
      unsafe("appearance", "none"),
      margin(px(0)),
      Styles.borderRadius(`base),
      outlineWidth(px(0)),
      fontWeight(`num(300)),
      borderWidth(px(0)),
      boxSizing(`borderBox),
      backgroundColor(`InputBg |> Styles.useColor),
      color(`BodyText |> Styles.useColor),
      border(px(1), `solid, (error ? `Error : `Border) |> Styles.useColor),
      transition(~duration=300, "all"),
      padding2(~v=`xs |> Styles.space, ~h=`sm |> Styles.space),
      focus([borderColor((error ? `Error : `Primary) |> Styles.useColor)]),
      placeholder([color(`Placeholder |> Styles.useColor)]),
      ...Styles.font(`base),
    ]);

  let label = () =>
    style([
      display(`block),
      marginBottom(`custom(1) |> Styles.space),
      color(`SecondaryText |> Styles.useColor),
      ...Styles.font(`sm),
    ]);
};

module InputContainer = {
  [@react.component]
  let make = (~label=?, ~className="", ~children) => {
    <div className={Css.merge([Classes.root, className])}>
      {label->Belt.Option.mapWithDefault(React.null, labelText =>
         <label className={Classes.label()}>
           {React.string(labelText)}
         </label>
       )}
      children
    </div>;
  };
};

[@react.component]
let make =
    (
      ~value=?,
      ~className="",
      ~onChange=?,
      ~multiline=false,
      ~placeholder=?,
      ~label=?,
      ~type_=?,
      ~error=false,
    ) => {
  <InputContainer ?label className>
    {multiline
       ? <textarea
           ?type_
           ?placeholder
           ?value
           ?onChange
           rows=3
           className={Classes.input(~error)}
         />
       : <input
           ?type_
           ?placeholder
           ?value
           ?onChange
           className={Classes.input(~error)}
         />}
  </InputContainer>;
};

module NativeSelect = {
  [@react.component]
  let make =
      (
        ~value=?,
        ~className="",
        ~onChange=?,
        ~multiline=false,
        ~placeholder=?,
        ~label=?,
        ~children,
        ~error=false,
      ) => {
    <InputContainer ?label className>
      <select ?value ?onChange ?placeholder className={Classes.input(~error)}>
        children
      </select>
    </InputContainer>;
  };
};
