module mousetrap
    using CxxWrap

    struct Vector2{T}
        x::T
        y::T
    end
    const Vector2f = Vector2{Float32}
    const Vector2i = Vector2{Int64}
    const Vector2ui = Vector2{UInt64}

    struct Vector3{T}
        x::T
        y::T
        z::T
    end
    const Vector3f = Vector3{Float32}
    const Vector3i = Vector3{Int64}
    const Vector3ui = Vector3{UInt64}

    struct Vector4{T}
        x::T
        y::T
        z::T
        w::T
    end
    const Vector4f = Vector4{Float32}
    const Vector4i = Vector4{Int64}
    const Vector4ui = Vector4{UInt64}

    const ActionID = String
    const ApplicationID = String
    const LogDomain = String
    const ShortcutTriggerID = String

    function __init__()
        @initcxx
    end

    @wrapmodule("./libmousetrap_julia_binding.so")
end

struct State
    window::mousetrap.Window
end
const state = Ref{Union{State, Nothing}}(nothing)

app = mousetrap.Application("test.app")

function activate(app)
    state = State(mousetrap.Window(app))
    mousetrap.set_title(state.window, "Hello Julia")
    #mousetrap.log_warning("test warning", "Julia")
    mousetrap.present(state.window)
    return nothing
end

mousetrap.connect_signal_activate(app, activate)

@show mousetrap.run(app)
