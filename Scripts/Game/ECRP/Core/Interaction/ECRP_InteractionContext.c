// Carries the participants involved in an interaction request.
// The context is deliberately immutable so action implementations receive a
// consistent view of the actor and target throughout validation and execution.
class ECRP_InteractionContext
{
	protected IEntity m_Actor;
	protected IEntity m_Target;

	// Creates a context for an actor attempting to interact with a target.
	void ECRP_InteractionContext(IEntity actor, IEntity target)
	{
		m_Actor = actor;
		m_Target = target;
	}

	// Returns the entity that initiated the interaction request.
	IEntity GetActor()
	{
		return m_Actor;
	}

	// Returns the entity that owns the interaction.
	IEntity GetTarget()
	{
		return m_Target;
	}

	// Returns true when both participants are available.
	bool IsValid()
	{
		return m_Actor && m_Target;
	}
}
