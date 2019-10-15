open DesignSystem;

module Classes = {
  open Css;

  let root = style([display(`flex), flexDirection(column)]);

  let header =
    style([
      marginBottom(`md |> Styles.space),
      fontWeight(`light),
      ...Styles.font(`md),
    ]);

  let gutter = style([marginBottom(`lg |> Styles.space)]);
};

let getInputValue = (e): string => ReactEvent.Form.target(e)##value;

[@react.component]
let make = () => {
  let (date, setDate) =
    React.useState(() => Js.Date.make() |> Utils.toInputDateFormat);

  let options: array(SingleSelect.selectOption(string)) = [|
    {id: "1", name: "choose me", item: "1"},
    {id: "2", name: "choose me 2", item: "2"},
  |];

  <form
    className=Classes.root onSubmit={e => e->ReactEvent.Form.preventDefault}>
    <div className=Classes.header>
      {React.string("Someone said something cool?")}
    </div>
    <SingleSelect options selectedId=None onChange={item => Js.log(item)} />
    <TextField label="Citation" placeholder="What was it?" multiline=true />
    <TextField label="Author" placeholder="Who was it?" />
    <TextField
      value=date
      onChange={e => setDate(_ => e |> getInputValue)}
      label="Date"
      type_="date"
      placeholder="When was it?"
      className=Classes.gutter
    />
    <Button fullWidth=true variant=`Primary type_="submit">
      {React.string("Save citation")}
    </Button>
  </form>;
};
