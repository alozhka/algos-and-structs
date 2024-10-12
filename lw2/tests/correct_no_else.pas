program TestProgram;

type
  TPerson = record
    Name: string;
    Age: integer;
  end;

var
  person: TPerson;
  counter: integer;

begin
  person.Name := 'John';
  person.Age := 30;
  counter := 0;

  repeat
    if person.Age > 18
    then
      begin
        writeln('Adult');
        if person.Age < 65
        then
          begin
            writeln('Working age');
          end
        else
          begin
            writeln('Retired');
          end;
      end
  until counter = 3;

  writeln('End of the program');
end.
