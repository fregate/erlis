-module(piped).

-export([
    init/1,
	evaluate_expression/1
]).

init([PipePath]) ->
	Pipe = open_port(PipePath, [eof]),
	run(Pipe).

run(Socket) ->
	receive
		{Socket, {data, Data}} -> parse(Data, Socket)
	end.

parse(Data, Socket) ->
	case Data of
		"exit" ->
			ok;
		_ ->
			evaluate_expression(Data),
			run(Socket)
	end.

evaluate_expression(Expression) ->
	{ok, Tokens, _} = erl_scan:string(Expression),    % scan the code into tokens
	{ok, Parsed} = erl_parse:parse_exprs(Tokens),     % parse the tokens into an abstract form
	{value, Result, _} = erl_eval:exprs(Parsed, []),  % evaluate the expression, return the value
	Result.
